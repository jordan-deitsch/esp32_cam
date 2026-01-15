#ifndef DEVICE_SETUP_H
#define DEVICE_SETUP_H

#include <cstdint>

// ===========================
// Define I2C pins and frequency
// ===========================
const int I2C_SDA_PIN = 13;
const int I2C_SCL_PIN = 14;
const uint32_t iic_frequency = 200000;

// ===========================
// Define SX1509 I2C address and pin usage
// ===========================
const uint8_t SX1509_ADDRESS = 0x3E; // SX1509 I2C address: set by ADDR1 and ADDR0 (00 by default)
const uint8_t SX1509_LED_PIN = 0;
const uint8_t SX1509_PWMA_PIN = 11;
const uint8_t SX1509_AI1_PIN = 10;
const uint8_t SX1509_AI2_PIN = 9;
const uint8_t SX1509_STBY_PIN = 8;

// Motor specific offset for direction (-1 for reverse polarity)
const int offsetA = 1;

#endif