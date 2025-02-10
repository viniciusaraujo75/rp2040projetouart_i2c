#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "ssd1306.h"
#include "ws2812.h"

// Definições dos pinos
#define LED_VERDE 11
#define LED_AMARELO 12
#define LED_VERMELHO 13
#define BOTAO 10

#define LED_RGB 14  // Pino do WS2812
#define I2C_PORT i2c1
#define SDA_PIN 6
#define SCL_PIN 7

#define UART_ID uart0
#define TX_PIN 0
#define RX_PIN 1
#define BAUD_RATE 115200

volatile bool botao_pressionado = false;

// Função de callback para o botão
void botao_callback(uint gpio, uint32_t eventos) {
    if (eventos & GPIO_IRQ_EDGE_FALL) {
        botao_pressionado = true;
    }
}

int main() {
    stdio_init_all();

    // Configuração da UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    // Configuração dos LEDs comuns
    gpio_init(LED_VERDE);
    gpio_init(LED_AMARELO);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    // Configuração do LED RGB WS2812
    ws2812_init(LED_RGB);

    // Configuração do botão com interrupção
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &botao_callback);

    // Inicializa o display OLED SSD1306
    ssd1306_init(I2C_PORT, SDA_PIN, SCL_PIN);
    ssd1306_print_text(10, 10, "Sistema Iniciado");

    while (1) {
        // Verifica se recebeu algo pela UART
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            printf("Recebido: %c\n", c);

            // Exibe no display
            char msg[20];
            snprintf(msg, sizeof(msg), "RX: %c", c);
            ssd1306_clear();
            ssd1306_print_text(10, 10, msg);
        }

        // Verifica se o botão foi pressionado
        if (botao_pressionado) {
            botao_pressionado = false;
            printf("Botão pressionado!\n");

            // Muda os LEDs
            gpio_put(LED_VERDE, 1);
            sleep_ms(500);
            gpio_put(LED_VERDE, 0);
            gpio_put(LED_AMARELO, 1);
            sleep_ms(500);
            gpio_put(LED_AMARELO, 0);
            gpio_put(LED_VERMELHO, 1);
            sleep_ms(500);
            gpio_put(LED_VERMELHO, 0);

            // Pisca o WS2812
            ws2812_set_color(LED_RGB, 255, 0, 0);
            sleep_ms(500);
            ws2812_set_color(LED_RGB, 0, 255, 0);
            sleep_ms(500);
            ws2812_set_color(LED_RGB, 0, 0, 255);
            sleep_ms(500);
            ws2812_set_color(LED_RGB, 0, 0, 0);
        }

        sleep_ms(100);
    }
}
