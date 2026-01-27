#ifndef DEVICE_SETUP_H
#define DEVICE_SETUP_H

#include <cstdint>

// ===========================
// Enter your WiFi credentials
// ===========================
inline constexpr char *ssid = "LogIntoMordor";
inline constexpr char *password = "1network2rule";

// ===========================
// Total number of sensors for webserver reporting
// ===========================
inline constexpr uint32_t NUM_SENSORS = 7;

// ===========================
// Define ESP32 I2C pins and frequency
// ===========================
inline constexpr uint32_t I2C_SDA_PIN = 13;
inline constexpr uint32_t I2C_SCL_PIN = 14;
inline constexpr uint32_t I2C_FREQUENCY = 200000;

// ===========================
// Define ADS1015 I2C address and pin usage
// ===========================
inline constexpr uint8_t ADS1015_ADDRESS = 0x48; // ADS1015 I2C address: set by ADDR pin

// ===========================
// Define SX1509 I2C address and pin usage
// ===========================
inline constexpr uint8_t SX1509_ADDRESS = 0x3E; // SX1509 I2C address: set by ADDR1 and ADDR0 pins
inline constexpr uint8_t SX1509_LED_RED_PIN = 0;
inline constexpr uint8_t SX1509_LED_GREEN_PIN = 1;
inline constexpr uint8_t SX1509_LED_BLUE_PIN = 2;
inline constexpr uint8_t SX1509_PWMA_PIN = 11;
inline constexpr uint8_t SX1509_AI1_PIN = 10;
inline constexpr uint8_t SX1509_AI2_PIN = 9;
inline constexpr uint8_t SX1509_STBY_PIN = 8;

// ===========================
// Define BMA400 I2C address and pin usage
// ===========================
inline constexpr uint8_t BMA400_ADDRESS = 0x14; // default BMA400 I2C address


#endif