#include "twi.h"

void twi_init(){

    // SCL pin, S0D1, Input, Use pullup
    GPIO->PIN_CNF[SCL] = (1 << 10) | (1 << 9) | (1 << 3) | (1 << 2);
    // SDA pin, S0D1, Input, Use pullup
    GPIO->PIN_CNF[SDA] = (1 << 10) | (1 << 9) | (1 << 3) | (1 << 2);

    TWIO->RXDRDY = 0;
    TWIO->TXDSENT = 0;
    TWIO->ERROR = 0;

    TWIO->PSELSCL = SCL;
    TWIO->PSELSDA = SDA;

    // 100 kHz
    TWIO->FREQUENCY = 0x01980000;

    // 5: Enable, 0: Disable
    TWIO->ENABLE = 5;
}

void twi_multi_read(uint8_t slave_address, uint8_t start_register, int registers_to_read, uint8_t *data_buffer) {
    TWIO->ADDRESS = slave_address;
    TWIO->TXDSENT = 0;
    TWIO->STARTTX = 1;
    TWIO->TXD = start_register;

    while(!TWIO->TXDSENT);
    
    TWIO->STARTRX = 1;
    for (int i = 0; i < registers_to_read; i++)
    {
        while(!(TWIO->RXDRDY));
        if(i == registers_to_read - 1){
            TWIO->STOP = 1;
        }
        TWIO->RXDRDY = 0;
        data_buffer[i] = TWIO->RXD;
    }
}

void twi_multi_write(uint8_t slave_address, uint8_t start_register, int registers_to_write, uint8_t* data_buffer){
    TWIO->ADDRESS = slave_address;
    TWIO->STARTTX = 1;
    TWIO->TXDSENT = 0;
    TWIO->TXD = start_register;

    while(!TWIO->TXDSENT);
    
    for(int i = 0; i < registers_to_write; i++){
        TWIO->TXDSENT = 0;
        TWIO->TXD = data_buffer[i];
        while(!TWIO->TXDSENT);
    }
    TWIO->STOP = 0;
}