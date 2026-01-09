import requests
import time
import cv2

ESP32_IP = "10.0.0.104"
SENSOR_URL = f"http://{ESP32_IP}/sensor"
STREAM_URL = f"http://{ESP32_IP}:81/stream"

THRESHOLD = 2000
POLL_INTERVAL = 0.5
CAPTURE_SECONDS = 10

def record_video(filename, duration):
    cap = cv2.VideoCapture(STREAM_URL)
    if not cap.isOpened():
        raise RuntimeError(f"Failed to open MJPEG stream at {STREAM_URL}")
        return

    fps = 20
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    fourcc = cv2.VideoWriter.fourcc(*"XVID")
    out = cv2.VideoWriter(filename, fourcc, fps, (width, height))

    start = time.time()
    while time.time() - start < duration:
        ret, frame = cap.read()
        if not ret:
            break
        out.write(frame)

    cap.release()
    out.release()
    print(f"Saved {filename}")

def poll_sensor():
    while True:
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

        time.sleep(POLL_INTERVAL)

if __name__ == "__main__":
    poll_sensor()
