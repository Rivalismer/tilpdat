#include "uart.h"
#include "gpio.h"

void uart_init(){
    GPIO->PIN_CNF[PIN_RXD] = 0;
    GPIO->PIN_CNF[PIN_TXD] = 0x1;
    UART->INTEN = 0;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->PSELTXD = 1 << PIN_TXD;
    UART->PSELRXD = 1 << PIN_RXD;
    UART->BAUDRATE = 0x00275000;
    UART->ENABLE = 4;
    UART->STARTRX = 1;
}