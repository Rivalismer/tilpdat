#include "uart.h"
#include "gpio.h"

void uart_init(){

    GPIO->PIN_CNF[PIN_RXD] = 0;
    GPIO->PIN_CNF[PIN_TXD] = 1;
    UART->INTENCLR = 0xFFFFFFFF;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->PSELTXD = PIN_TXD;
    UART->PSELRXD = PIN_RXD;
    UART->BAUDRATE = 0x00275000;
    UART->ENABLE = 4;
    UART->STARTRX = 1;
}

void uart_send(char letter){
    UART->STARTTX = 1;
    UART->TXDRDY = 0;
    UART->TXD = letter;

    while(!(UART->TXDRDY)){ }
    
    UART->TXDRDY = 0;
    UART->STOPTX = 1;
}


char uart_read(){
    UART->STARTRX = 1;
    
    if(UART->RXDRDY){
        UART->RXDRDY = 0;
        return UART->RXD;
    }

    return '\0';
}
