import requests
import time
import cv2

ESP32_IP = "10.0.0.104"
SENSOR_URL = f"http://{ESP32_IP}/sensor"
STREAM_URL = f"http://{ESP32_IP}:81/stream"

THRESHOLD = 2000
POLL_INTERVAL = 0.5
CAPTURE_SECONDS = 5
CALIBRATION_SECONDS = 5
ACTUAL_FPS = 50

def calibrate_fps():
    cap = cv2.VideoCapture(STREAM_URL)
    if not cap.isOpened():
        raise RuntimeError(f"Failed to open MJPEG stream at {STREAM_URL}")
        return

    frame_count = 0
    start_time = time.time()

    print("Calibrating camera FPS...")

    while time.time() - start_time < CALIBRATION_SECONDS:
        ret, frame = cap.read()
        if not ret:
            break
        frame_count += 1

    elapsed = time.time() - start_time
    global ACTUAL_FPS
    ACTUAL_FPS = frame_count / elapsed
    print(f"Calibrated {frame_count} frames in {elapsed:.2f} seconds ({ACTUAL_FPS:.2f} FPS)")

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

def poll_sensor():
    try:
        r = requests.get(SENSOR_URL, timeout=1)
        value = r.json()["value"]
        print("Sensor:", value)

        if value >= THRESHOLD:
            ts = int(time.time())
            record_video(f"capture_{ts}.avi", CAPTURE_SECONDS)
            time.sleep(2)  # debounce

    except Exception as e:
        print("Error:", e)


# Perform setup and calibration of camera
calibrate_fps()

# Poll sensor data and wait for capture trigger
while True:
    poll_sensor()
    time.sleep(POLL_INTERVAL)
