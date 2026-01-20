#ifndef DEVICE_SETUP_H
#define DEVICE_SETUP_H

#include <cstdint>

// ===========================
// Define I2C pins and frequency
// ===========================
inline constexpr uint32_t I2C_SDA_PIN = 13;
inline constexpr uint32_t I2C_SCL_PIN = 14;
inline constexpr uint32_t I2C_FREQUENCY = 200000;

// ===========================
// Define SX1509 I2C address and pin usage
// ===========================
inline constexpr uint8_t SX1509_ADDRESS = 0x3E; // SX1509 I2C address: set by ADDR1 and ADDR0 (00 by default)
inline constexpr uint8_t SX1509_LED_RED_PIN = 0;
inline constexpr uint8_t SX1509_LED_GREEN_PIN = 1;
inline constexpr uint8_t SX1509_LED_BLUE_PIN = 2;
inline constexpr uint8_t SX1509_PWMA_PIN = 11;
inline constexpr uint8_t SX1509_AI1_PIN = 10;
inline constexpr uint8_t SX1509_AI2_PIN = 9;
inline constexpr uint8_t SX1509_STBY_PIN = 8;

#endif