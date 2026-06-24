# ESP32_BME280_I2C_test
Test I2C connection between an ESP32 chip and a BME280 sensor

## Purpose

* Helper script to test I2C connection between an ESP32 chip and a BME280 sensor.

## Longer version

The script is build to check whether the basic I2C connection between the sensor and the ESP32 works. That way I can check to rule out that the physical connections between the pins pose any issues. I checked it both on a setup with the version sold by SEENGREAT (connection is established) and another chip with number GYBMEP where the script identified the CHIP ID at register 0xE3 instead of 0xD0 which is the default for BME280. It checks both I2C addresses (0x76 and 0x77) and reports on which address the chip answers.
