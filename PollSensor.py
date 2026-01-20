import requests
import time
from datetime import datetime
import cv2

# Define web server URL (may change with build machines, WiFi network, or ESP32)
ESP32_IP = "10.0.0.77"
SENSOR_URL = f"http://{ESP32_IP}/sensor_json"
STREAM_URL = f"http://{ESP32_IP}:81/stream"

THRESHOLD = 0.8             # Sensor threshold to initiate video capture
POLL_INTERVAL = 0.5         # Interval between polling times for JSON sensor data
CAPTURE_SECONDS = 10        # Duration of video capture after threshold trigger
CALIBRATION_SECONDS = 5     # Duration of frame rate calibration
ACTUAL_FPS = 50             # Set initial value before calculating


# Capture frames for defined calibration period and calculate FPS
def calibrate_fps(calibration_time):
    cap = cv2.VideoCapture(STREAM_URL)
    if not cap.isOpened():
        raise RuntimeError(f"Failed to open MJPEG stream at {STREAM_URL}")
        return

    # Initialize number of frames and starting time
    frame_count = 0
    start_time = time.time()

    print("Calibrating camera FPS...")

    # Count frames during calibration time
    while time.time() - start_time < calibration_time:
        ret, frame = cap.read()
        if not ret:
            break
        frame_count += 1

    # Calculate FPS from number of frames and elapsed time
    actual_elapsed = time.time() - start_time
    global ACTUAL_FPS
    ACTUAL_FPS = frame_count / actual_elapsed
    print(f"Calibrated {frame_count} frames in {actual_elapsed:.2f} seconds ({ACTUAL_FPS:.2f} FPS)")


# Record video for requested duration and save to file (.avi)
def record_video(filename, duration):
    cap = cv2.VideoCapture(STREAM_URL)
    if not cap.isOpened():
        raise RuntimeError(f"Failed to open MJPEG stream at {STREAM_URL}")
        return

    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    fourcc = cv2.VideoWriter.fourcc(*"XVID")
    out = cv2.VideoWriter(filename, fourcc, ACTUAL_FPS, (width, height))

    frame_count = 0
    start_time = time.time()

    print("Starting recording")
    while time.time() - start_time < CAPTURE_SECONDS:
        ret, frame = cap.read()
        if not ret:
            break
        out.write(frame)
        frame_count += 1

    elapsed = time.time() - start_time
    actual_fps = frame_count / elapsed
    print(f"Captured {frame_count} frames in {elapsed:.2f} seconds ({actual_fps:.2f} FPS)")

    cap.release()
    out.release()
    print(f"Saved {filename}")


# Poll JSON sensor data and compare to threshold for video capture
def poll_sensor():
    try:
        r = requests.get(SENSOR_URL, timeout=1)
        val0 = r.json()["sensor_a0"]
        val1 = r.json()["sensor_a1"]
        val2 = r.json()["sensor_a2"]
        val3 = r.json()["sensor_a3"]

        print(f"A0: {val0:.3f} A1: {val1:.3f} A2: {val2:.3f} A3: {val3:.3f}")

        # Use val0 for threshold comparison
        if val0 >= THRESHOLD:
            ts = int(time.time())
            timestamp_str = datetime.fromtimestamp(ts).strftime("%Y_%b_%d_%H_%M_%S")
            record_video(f"capture_{timestamp_str}.avi", CAPTURE_SECONDS)
            time.sleep(2)  # Allow time for sensor to recover after video capture complete

    except Exception as e:
        print("Error:", e)


# Perform setup and calibration of camera
calibrate_fps(CALIBRATION_SECONDS)

# Poll sensor data and wait for capture trigger
while True:
    poll_sensor()
    time.sleep(POLL_INTERVAL)
