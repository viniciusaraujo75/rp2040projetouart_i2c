#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "uart_handler.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0  
#define UART_RX_PIN 1  

void uart_init_custom() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

char uart_receive_char() {
    while (!uart_is_readable(UART_ID)) {}  
    return uart_getc(UART_ID);
}
