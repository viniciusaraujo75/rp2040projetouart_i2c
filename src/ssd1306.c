#include "ssd1306.h"
#include "font.h"  // Arquivo com as fontes (deve estar na pasta src/)
#include "hardware/i2c.h"
#include "pico/stdlib.h"

static uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
static i2c_inst_t *ssd1306_i2c;

void ssd1306_send_command(uint8_t command) {
    uint8_t buf[2] = {0x00, command};
    i2c_write_blocking(ssd1306_i2c, SSD1306_I2C_ADDR, buf, 2, false);
}

void ssd1306_init(i2c_inst_t *i2c, uint sda, uint scl) {
    ssd1306_i2c = i2c;

    i2c_init(i2c, 400 * 1000);  // 400 kHz
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);

    sleep_ms(100);

    ssd1306_send_command(0xAE);  // Desliga o display
    ssd1306_send_command(0xD5);
    ssd1306_send_command(0x80);
    ssd1306_send_command(0xA8);
    ssd1306_send_command(SSD1306_HEIGHT - 1);
    ssd1306_send_command(0xD3);
    ssd1306_send_command(0x00);
    ssd1306_send_command(0x40);
    ssd1306_send_command(0x8D);
    ssd1306_send_command(0x14);
    ssd1306_send_command(0x20);
    ssd1306_send_command(0x00);
    ssd1306_send_command(0xA1);
    ssd1306_send_command(0xC8);
    ssd1306_send_command(0xDA);
    ssd1306_send_command(0x12);
    ssd1306_send_command(0x81);
    ssd1306_send_command(0xCF);
    ssd1306_send_command(0xD9);
    ssd1306_send_command(0xF1);
    ssd1306_send_command(0xDB);
    ssd1306_send_command(0x40);
    ssd1306_send_command(0xA4);
    ssd1306_send_command(0xA6);
    ssd1306_send_command(0xAF);  // Liga o display

    ssd1306_clear();
    ssd1306_show();
}

void ssd1306_clear() {
    for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = 0x00;
    }
}

void ssd1306_draw_pixel(int x, int y, bool color) {
    if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT) return;

    if (color) {
        buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y % 8));
    } else {
        buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

void ssd1306_show() {
    uint8_t buf[SSD1306_WIDTH + 1];
    buf[0] = 0x40;

    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_send_command(0xB0 + page);
        ssd1306_send_command(0x00);
        ssd1306_send_command(0x10);

        for (uint8_t i = 0; i < SSD1306_WIDTH; i++) {
            buf[i + 1] = buffer[i + SSD1306_WIDTH * page];
        }

        i2c_write_blocking(ssd1306_i2c, SSD1306_I2C_ADDR, buf, sizeof(buf), false);
    }
}

void ssd1306_print_text(int x, int y, const char *text) {
    while (*text) {
        uint8_t c = *text++;
        if (c < 32 || c > 127) c = '?';

        for (int i = 0; i < 6; i++) {
            uint8_t line = font6x8[c - 32][i];

            for (int j = 0; j < 8; j++) {
                ssd1306_draw_pixel(x + i, y + j, (line >> j) & 1);
            }
        }
        x += 6;
    }
    ssd1306_show();
}
