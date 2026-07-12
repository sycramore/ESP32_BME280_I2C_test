#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c_master.h"

#define I2C_MASTER_SCL_IO      6
#define I2C_MASTER_SDA_IO      5
#define I2C_MASTER_FREQ_HZ     100000

#define BME280_ADDR_1          0x76
#define BME280_ADDR_2          0x77
#define BME280_CHIP_ID_REG     0xD0
#define BME280_EXPECTED_ID     0x60

static const char *TAG = "BME280_TEST";

static esp_err_t read_register(i2c_master_dev_handle_t dev_handle,
                               uint8_t reg_addr,
                               uint8_t *data)
{
    return i2c_master_transmit_receive(
        dev_handle,
        &reg_addr,
        1,
        data,
        1,
        pdMS_TO_TICKS(1000)
    );
}

void app_main(void)
{
    ESP_LOGI(TAG, "APP START");
    ESP_LOGI(TAG, "Initializing I2C master");

    i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus_handle;

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    uint8_t addresses[] = { BME280_ADDR_1, BME280_ADDR_2 };

    for (int i = 0; i < 2; i++) {
        uint8_t addr = addresses[i];

        ESP_LOGI(TAG, "Testing I2C address 0x%02X", addr);

        i2c_device_config_t dev_config = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = addr,
            .scl_speed_hz = I2C_MASTER_FREQ_HZ,
        };

        i2c_master_dev_handle_t dev_handle;

        esp_err_t err = i2c_master_bus_add_device(
            bus_handle,
            &dev_config,
            &dev_handle
        );

        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to add device 0x%02X: %s",
                     addr, esp_err_to_name(err));
            continue;
        }

        uint8_t chip_id = 0x00;

        err = read_register(dev_handle, BME280_CHIP_ID_REG, &chip_id);

        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Device answered at 0x%02X", addr);
            ESP_LOGI(TAG, "Chip ID register 0xD0 = 0x%02X", chip_id);

            if (chip_id == BME280_EXPECTED_ID) {
                ESP_LOGI(TAG, "BME280 found at address 0x%02X", addr);
            } else {
                ESP_LOGW(TAG, "Device found, but chip ID is not BME280");
            }
        } else {
            ESP_LOGW(TAG, "No valid response at 0x%02X: %s",
                     addr, esp_err_to_name(err));
        }

        ESP_ERROR_CHECK(i2c_master_bus_rm_device(dev_handle));
    }

    ESP_LOGI(TAG, "I2C test finished");

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
