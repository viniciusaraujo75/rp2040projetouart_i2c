#ifndef SSD1306_H
#define SSD1306_H

#include <stdio.h>
#include "hardware/i2c.h"

#define SSD1306_I2C_ADDR  0x3C  // Endereço padrão do SSD1306
#define SSD1306_WIDTH     128
#define SSD1306_HEIGHT    64

void ssd1306_init(i2c_inst_t *i2c, uint sda, uint scl);
void ssd1306_clear();
void ssd1306_draw_pixel(int x, int y, bool color);
void ssd1306_show();
void ssd1306_print_text(int x, int y, const char *text);
void ssd1306_send_command(uint8_t command);

#endif
