#include "twi.h"
#include "uart.h"
#include "accel.h"
#include "ubit_led_matrix.h"
#include <stdlib.h>

int main(){
    uart_init();
    twi_init();
    accel_init();
    ubit_led_matrix_init();

    int* data_buffer = (int*)malloc(3 * sizeof(int));

    while(1){
        accel_read_x_y_z(data_buffer);
        int x_acc = data_buffer[0];
        int y_acc = data_buffer[1];
        
        int x_dot = x_acc/3;
        int y_dot = -y_acc/3;

        ubit_led_matrix_light_only_at(x_dot, y_dot);
        utility_print(&uart_send, "X: %6d Y: %6d\n\r", x_acc, y_acc);
    }
    return 0;
}