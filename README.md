# ESP32-CAM
Development repository for ESP32-CAM microcontroller

Hardware Target:
AI Thinker ESP32-CAM

Python Dependencies:
pip install opencv-python
pip install requests

Arduino Libraries:
Sparkfun ADS1015 Arduino Library
SX1509 IO Expander

ESP32-CAM Pinout Guide:
https://lastminuteengineers.com/esp32-cam-pinout-reference/ 

Update ssid with network ID
Update password with network password

Access streamed camera feed at: http://10.0.0.77/
Access live sensor data at: http://10.0.0.77/sensor_data
Access sensor data via JSON at: http://10.0.0.77/sensor_json

Run PollSensor.py after ESP32-CAM is running to trigger camera capture at threshold.
When running the Python script you cannot also have the live browser stream running.