#ifndef DEVICE_SETUP_H
#define DEVICE_SETUP_H

#include <cstdint>

// ===========================
// Enter your WiFi credentials
// ===========================
inline constexpr char *ssid = "Jordan's iPhone";
inline constexpr char *password = "b1ysfp1jsdix5";

// ===========================
// Define ESP32 I2C pins and frequency
// ===========================
inline constexpr uint32_t I2C_SCL_PIN = 13;
inline constexpr uint32_t I2C_SDA_PIN = 14;
inline constexpr uint32_t I2C_FREQUENCY = 200000;

// ===========================
// Define ADS1015 I2C address and pin usage
// ===========================
inline constexpr uint8_t ADC_ADDRESS = 0x48; // ADS1015 I2C address: set by ADDR pin

// ===========================
// Define BME280 I2C address and pin usage
// ===========================
inline constexpr uint8_t BME280_ADDRESS = 0x76; // BME280 I2C address: set by ADDR pin

// ===========================
// Define  address and pin usage
// ===========================
const int NEOPIXEL_COUNT = 9;
inline constexpr uint8_t NEOPIXEL_PIN = 15;

// ===========================
// Define motor driver board pin usage
// ===========================
const int stepsPerRevolution = 2048;
inline constexpr uint8_t MOTOR_PIN_2 = 2;   // Wire color: Blue
inline constexpr uint8_t MOTOR_PIN_4 = 12;  // Cire color: Green

// TODO: stepper will spin when Yellow and White are removed (only one drive pair), issues driving motor pin 1
// inline constexpr uint8_t MOTOR_PIN_1 = 0;   // Wire color: Yellow -> NOT WORKING, tested on both IO0 and IO4
// inline constexpr uint8_t MOTOR_PIN_3 = 15;  // Wire color: White

#endif