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
inline constexpr uint32_t I2C_SDA_PIN = 14;
inline constexpr uint32_t I2C_SCL_PIN = 13;
inline constexpr uint32_t I2C_FREQUENCY = 200000;

// ===========================
// Define ADS1015 I2C address and pin usage
// ===========================
inline constexpr uint8_t ADS1015_ADDRESS = 0x48; // ADS1015 I2C address: set by ADDR pin

// ===========================
// Define BME280 I2C address and pin usage
// ===========================
inline constexpr uint8_t BME280_ADDRESS = 0x77; // BME280 I2C address: set by ADDR pin

// ===========================
// Define motor driver board pin usage
// ===========================
const int stepsPerRevolution = 2048;

inline constexpr uint8_t MOTOR_PIN_1 = 4;   // Color: 
inline constexpr uint8_t MOTOR_PIN_2 = 2;   // Color: 
inline constexpr uint8_t MOTOR_PIN_3 = 15;  // Color: 
inline constexpr uint8_t MOTOR_PIN_4 = 12;  // Color: 

#endif