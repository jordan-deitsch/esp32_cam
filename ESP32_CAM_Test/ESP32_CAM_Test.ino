// User defined sources
#include <WiFi.h>
#include <Wire.h>
#include "DeviceSetup.h"
#include "src/ADS1015/ADS1015.h"
#include "src/SX1509/SX1509.h"

// SparkFun Libraries
#include <Arduino.h>
#include <esp_camera.h>
#include <ADS1X15.h>
#include <SparkFunSX1509.h>
#include <SparkFunBME280.h>
#include <Adafruit_NeoPixel.h>

// ===========================
// Select camera model in board_config.h
// ===========================
#include "src/camera/board_config.h"

void startCameraServer();
void setupLedFlash();

// User functions
double calculate_gravity();
void print_bme_data();
void update_led_from_sensor(float sensor_val);
void set_neopixel_color(uint8_t red, uint8_t green, uint8_t blue);

// Webserver global variables
volatile float serverValueArr[8];
volatile uint16_t buttonValue = 0;

// User devices
BME280 bme280sensor; 
Adafruit_NeoPixel strip(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, I2C_FREQUENCY);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  Serial.println("Starting setup...");

  // Initialize ADC
  if (adcSensor.begin() == true)
  {
    Serial.println("ADS1015 device found. I2C connections are good.");
  }
  else
  {
    Serial.println("ADS1015 device not found. Check wiring.");
    while (1); // stall out forever
  }

  // Initialize GPIO expander
  if (gpio.begin(SX1509_ADDRESS) == true)
  {
    Serial.println("SX1509 device found. I2C connections are good.");
    SX1509_setup();
  }
  else
  {
    Serial.println("SX1509 device not found. Check wiring.");
    while (1); // stall out forever
  }

  // Initialize BME280 sensor
  bme280sensor.setI2CAddress(BME280_ADDRESS);
  if(bme280sensor.beginI2C() == true)
  {
    Serial.println("BME280 device found. I2C connections are good.");
  }
  else
  {
    Serial.println("BME280 device not found. Check wiring.");
    while (1); // stall out forever
  }

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG;  // for streaming
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if (config.pixel_format == PIXFORMAT_JPEG) {
    if (psramFound()) {
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
      Serial.println("PSRAM Found");
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
      Serial.println("PSRAM Missing");
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t *s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);        // flip it back
    s->set_brightness(s, 1);   // up the brightness just a bit
    s->set_saturation(s, -2);  // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  if (config.pixel_format == PIXFORMAT_JPEG) {
    s->set_framesize(s, FRAMESIZE_QVGA);
  }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif

// Setup LED FLash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
  setupLedFlash();
#endif

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  // Setup Neopixel strip with constant color
  strip.begin();
  strip.show();
}

void loop() {
  
  //
  // ADD MAIN LOOP CODE HERE
  //

  // Check webserver for button updates and perform any desired actions
  if(buttonValue != 0) {
    Serial.println("Button Pressed");
    buttonValue = 0;
    SX1509_stepper_move(STEPPER_STEPS_PER_REV);
  }

  // Read all data from ADC
  ADS1015_get_all_channels();
  
  // Check gravity
  double gravity = calculate_gravity();
  if(gravity < 0.8f){
    Serial.print("Low gravity: ");
    Serial.printf("%.3f", gravity);
    Serial.println();
    SX1509_stepper_move(STEPPER_STEPS_PER_REV);
  }

  // Check moisture level
  if(adcScaledArr[3] > 0.8f){
    Serial.print("Low moisture: ");
    Serial.printf("%d = %.3f", adcValueArr[3], adcScaledArr[3]);
    Serial.println();
    SX1509_stepper_move(STEPPER_STEPS_PER_REV);
  }

  // Set Neopixel color dynamically
  update_led_from_sensor(adcScaledArr[3]);  // Set color based on moisture level

  // Update sensor values for webserver with the ADC read values scaled to [0, 1]
  serverValueArr[0] = (float)gravity;   // Total gravity
  serverValueArr[1] = adcScaledArr[0];  // Gravity X
  serverValueArr[2] = adcScaledArr[1];  // Gravity Y
  serverValueArr[3] = adcScaledArr[2];  // Gravity Z
  serverValueArr[4] = adcScaledArr[3];  // Moisture
  serverValueArr[5] = (float)bme280sensor.readFloatHumidity();
  serverValueArr[6] = (float)bme280sensor.readFloatPressure();
  serverValueArr[7] = (float)bme280sensor.readTempF();

  // print_bme_data();
  // ADS1015_print_all_channels();
  
  delay(200);
}

// Calculate total gravity from X-Y-Z components
double calculate_gravity()
{
  double zero_bias_cal[3] = {0.498f, 0.492f, 0.525f}; // Each channel has slightly different offsets
  double one_g_scale = 0.1f;

  // Use standard distance formula to calculate gravity from x-y-z components
  double total_grav = sqrt( sq(adcScaledArr[0] - zero_bias_cal[0]) + 
                            sq(adcScaledArr[1] - zero_bias_cal[1]) + 
                            sq(adcScaledArr[2] - zero_bias_cal[2])    ) / one_g_scale;

  // for (int i=0; i<NUM_ADC_CHANNELS-1; i++)
  // {
  //   Serial.printf("Axis %d: %.3f  ", i, adcScaledArr[i]);
  // }
  // Serial.printf("Gravity: %f", total_grav);
  // Serial.println();
  
  return total_grav;
}

// Print all BME280 data to serial port
void print_bme_data()
{
  Serial.print("Humidity: ");
  Serial.print(bme280sensor.readFloatHumidity(), 0);

  Serial.print(" Pressure: ");
  Serial.print(bme280sensor.readFloatPressure(), 0);

  Serial.print(" Temp: ");
  Serial.print(bme280sensor.readTempF(), 2);
  // Serial.print(mySensorA.readTempC(), 2);

  Serial.println();
}

// Dynamically set NeoPixel strip color based on sensor value
void update_led_from_sensor(float sensor_val)
{
  // Verify that sensor value is percentage within range [0.0, 1.0]
  if(sensor_val > 1.0f)
  {
    sensor_val = 1.0f;
  }
  else if(sensor_val < 0.0f)
  {
    sensor_val = 0.0f;
  }

  float max_value = 255.0f;
  float red_val = max_value * sensor_val;           // 100% = all red (dry)
  float blue_val = max_value * (1.0f - sensor_val); // 0% = all blue (wet)

  // Serial.printf("Blue Light Value: %f", blue_val);
  // Serial.println();

  set_neopixel_color((uint8_t)red_val, 0, (uint8_t)blue_val);
}


// Colors in RGB, with each color in range [0, 255]
void set_neopixel_color(uint8_t red, uint8_t green, uint8_t blue)
{
  for(int i=0; i<NEOPIXEL_COUNT; i++)
  {
    strip.setPixelColor(i, red, green, blue);
  }

  strip.show();
}