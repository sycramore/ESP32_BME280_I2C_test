# ESP32_BME280_I2C_test
Test I2C connection between an ESP32 chip and a BME280 sensor

## Purpose

* Helper script to test I2C connection between an ESP32 chip and a BME280 sensor.

## Longer version

The script is build to check whether the basic I2C connection between the sensor and the ESP32 works. That way I can check to rule out that the physical connections between the pins pose any issues. I checked it both on a setup with the version sold by SEENGREAT (connection is established) and another chip with number GYBMEP where the script identified the CHIP ID at register 0xE3 instead of 0xD0 which is the default for BME280. It checks both I2C addresses (0x76 and 0x77) and reports on which address the chip answers.

## Development notes
Initial code scaffold was generated with ChatGPT. I2C addresses, WHO_AM_I register values, and chip ID discrepancies (see above) were verified through datasheet research and hands-on testing.

## Bugs

The folder [issues](.issues) contains documentation on issues I encountered during my work with ESP32 boards. They include issues with installation of the ESP-IDF framework on Linux and Mac OS, not recognizing different ESP boards by either operating system and other issues I had. As I did not find much documentation on some of those bugs I hope this collection is helpful for other people facing the same issues I had. Issues are grouped by type of issue. [Connection issues](./issues/connection_issues) refers to cases where ESP-IDF is installed and should work but the board is not recognized. [Framework issues](./issues/framework_issues). [Chip issues](./issues/chip_issues) contains pictures for the case where the script identified the CHIP ID at the "wrong" register 0xE3.
