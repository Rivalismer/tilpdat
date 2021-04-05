#include "twi.h"

void twi_init(){
    GPIO->DIRCLR = 1 << SDA;
    GPIO->DIRCLR = 1 << SCL;

    GPIO->PIN_CNF[SDA] = 6 << 8 | (3<<2);
    GPIO->PIN_CNF[SCL] = 6 << 8 | (3<<2);

    TWIO->PSELSCL = SCL;
    TWIO->PSELSDA = SDA;

    TWIO->FREQUENCY = 0x01980000;
    TWIO->ENABLE = 5;
    //TWIO->STARTRX = 1;
}

void twi_multi_read(uint8_t slave_address, uint8_t start_register, int registers_to_read, uint8_t *data_buffer) {
    TWIO->ADDRESS = slave_address;
    TWIO->STARTTX = 1;
    TWIO->TXDSENT = 0;
    TWIO->TXD = start_register;

    while(!(TWIO->TXDSENT));
    utility_print(&uart_send, "Currently pre-for: %d\n\r", 1);

    for (int i = 0; i < registers_to_read; i++)
    {
        while(!(TWIO->RXDRDY));
        TWIO->RXDRDY = 0;
        *(data_buffer + i) = TWIO->RXD;
        utility_print(&uart_send, "Currently in-for: %d\n\r", 1);
    }
    TWIO->STOP = 1;
    TWIO->STARTRX = 1;
}