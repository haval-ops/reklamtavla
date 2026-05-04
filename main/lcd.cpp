#include "lcd.h"

#include <string>

#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_FREQ_HZ 100000

#define LCD_ADDR 0x27

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_COMMAND 0x00
#define LCD_DATA 0x01

static void i2cWriteByte(uint8_t data) {
    i2c_master_write_to_device(
        I2C_MASTER_NUM,
        LCD_ADDR,
        &data,
        1,
        pdMS_TO_TICKS(100)
    );
}

static void lcdPulseEnable(uint8_t data) {
    i2cWriteByte(data | LCD_ENABLE | LCD_BACKLIGHT);
    vTaskDelay(pdMS_TO_TICKS(1));

    i2cWriteByte((data & ~LCD_ENABLE) | LCD_BACKLIGHT);
    vTaskDelay(pdMS_TO_TICKS(1));
}

static void lcdWrite4Bits(uint8_t value) {
    i2cWriteByte(value | LCD_BACKLIGHT);
    lcdPulseEnable(value);
}

static void lcdSend(uint8_t value, uint8_t mode) {
    uint8_t highNibble = value & 0xF0;
    uint8_t lowNibble = (value << 4) & 0xF0;

    lcdWrite4Bits(highNibble | mode);
    lcdWrite4Bits(lowNibble | mode);
}

static void lcdCommand(uint8_t command) {
    lcdSend(command, LCD_COMMAND);
}

static void lcdWriteChar(char c) {
    lcdSend(static_cast<uint8_t>(c), LCD_DATA);
}

void lcdInit() {
    i2c_config_t config = {};
    config.mode = I2C_MODE_MASTER;
    config.sda_io_num = I2C_MASTER_SDA_IO;
    config.scl_io_num = I2C_MASTER_SCL_IO;
    config.sda_pullup_en = GPIO_PULLUP_ENABLE;
    config.scl_pullup_en = GPIO_PULLUP_ENABLE;
    config.master.clk_speed = I2C_MASTER_FREQ_HZ;

    i2c_param_config(I2C_MASTER_NUM, &config);
    i2c_driver_install(I2C_MASTER_NUM, config.mode, 0, 0, 0);

    vTaskDelay(pdMS_TO_TICKS(50));

    lcdWrite4Bits(0x30);
    vTaskDelay(pdMS_TO_TICKS(5));

    lcdWrite4Bits(0x30);
    vTaskDelay(pdMS_TO_TICKS(5));

    lcdWrite4Bits(0x30);
    vTaskDelay(pdMS_TO_TICKS(5));

    lcdWrite4Bits(0x20);
    vTaskDelay(pdMS_TO_TICKS(5));

    lcdCommand(0x28);
    lcdCommand(0x0C);
    lcdCommand(0x06);
    lcdClear();
}

void lcdClear() {
    lcdCommand(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcdSetCursor(int col, int row) {
    const int rowOffsets[] = {0x00, 0x40};
    lcdCommand(0x80 | (col + rowOffsets[row]));
}

void lcdPrint(const std::string& text) {
    for (char c : text) {
        lcdWriteChar(c);
    }
}

static std::string fitToLcdWidth(const std::string& text) {
    if (text.length() <= 16) {
        return text;
    }

    return text.substr(0, 16);
}

static void showStaticText(const AdMessage& ad, const std::string& customerName, int durationSeconds) {
    lcdClear();

    lcdSetCursor(0, 0);
    lcdPrint(fitToLcdWidth(customerName));

    lcdSetCursor(0, 1);
    lcdPrint(fitToLcdWidth(ad.text));

    vTaskDelay(pdMS_TO_TICKS(durationSeconds * 1000));
}

static void showBlinkText(const AdMessage& ad, const std::string& customerName, int durationSeconds) {
    int elapsedMs = 0;
    const int intervalMs = 500;

    while (elapsedMs < durationSeconds * 1000) {
        lcdClear();

        lcdSetCursor(0, 0);
        lcdPrint(fitToLcdWidth(customerName));

        lcdSetCursor(0, 1);
        lcdPrint(fitToLcdWidth(ad.text));

        vTaskDelay(pdMS_TO_TICKS(intervalMs));
        elapsedMs += intervalMs;

        lcdClear();

        vTaskDelay(pdMS_TO_TICKS(intervalMs));
        elapsedMs += intervalMs;
    }
}

static void showScrollText(const AdMessage& ad, const std::string& customerName, int durationSeconds) {
    const int lcdWidth = 16;
    const int intervalMs = 300;

    std::string padding(lcdWidth, ' ');
    std::string fullText = padding + ad.text + padding;

    int elapsedMs = 0;

    while (elapsedMs < durationSeconds * 1000) {
        for (int i = 0; i <= static_cast<int>(fullText.length()) - lcdWidth; i++) {
            lcdClear();

            lcdSetCursor(0, 0);
            lcdPrint(fitToLcdWidth(customerName));

            lcdSetCursor(0, 1);
            lcdPrint(fullText.substr(i, lcdWidth));

            vTaskDelay(pdMS_TO_TICKS(intervalMs));
            elapsedMs += intervalMs;

            if (elapsedMs >= durationSeconds * 1000) {
                break;
            }
        }
    }
}

void showAdOnLcd(const AdMessage& ad, const std::string& customerName, int durationSeconds) {
    switch (ad.mode) {
        case STATIC_TEXT:
            showStaticText(ad, customerName, durationSeconds);
            break;

        case SCROLL_TEXT:
            showScrollText(ad, customerName, durationSeconds);
            break;

        case BLINK_TEXT:
            showBlinkText(ad, customerName, durationSeconds);
            break;

        default:
            showStaticText(ad, customerName, durationSeconds);
            break;
    }
}
