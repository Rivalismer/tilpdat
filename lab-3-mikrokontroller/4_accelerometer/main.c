#include "twi.h"
#include "uart.h"
#include "utility.h"
#include <stdlib.h>

int main(){
    uart_init();
    twi_init();

    uint8_t* data_buffer;
    data_buffer = (uint8_t*)malloc(8 * sizeof(uint8_t));

    twi_multi_read(0x1D, 0x0D, 1, data_buffer);
    utility_print(&uart_send, "Num: %d\n\r", (int)*data_buffer);
    free(data_buffer);

    while(1);
    return 0;
}