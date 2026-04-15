#ifndef DEVICE_SETUP_H
#define DEVICE_SETUP_H

#include <cstdint>

// ===========================
// Enter your WiFi credentials
// ===========================
inline constexpr char *ssid = "LogIntoMordor";
inline constexpr char *password = "1network2rule";

// ===========================
// Define ESP32 I2C pins and frequency
// ===========================
inline constexpr uint32_t I2C_SCL_PIN = 13;
inline constexpr uint32_t I2C_SDA_PIN = 14;
inline constexpr uint32_t I2C_FREQUENCY = 400000;

// ===========================
// Define ADS1015 I2C address and pin usage
// ===========================
inline constexpr uint8_t ADC_ADDRESS = 0x48; // ADS1015 I2C address: set by ADDR pin

// ===========================
// Define BME280 I2C address and pin usage
// ===========================
inline constexpr uint8_t BME280_ADDRESS = 0x76; // BME280 I2C address: set by ADDR pin

// ===========================
// Define SX1509 I2C address and pin usage
// ===========================
inline constexpr uint8_t SX1509_ADDRESS = 0x3E; // SX1509 I2C address: set by ADDR1 and ADDR0 pins
inline constexpr uint8_t SX1509_A_PIN = 0;
inline constexpr uint8_t SX1509_B_PIN = 1;
inline constexpr uint8_t SX1509_C_PIN = 2;
inline constexpr uint8_t SX1509_D_PIN = 3;

// ===========================
// Define  address and pin usage
// ===========================
const int NEOPIXEL_COUNT = 9;
inline constexpr uint8_t NEOPIXEL_PIN = 15;

#endif