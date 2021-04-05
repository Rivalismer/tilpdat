#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"

#define __BUTTON_A_PIN__	17
#define __BUTTON_B_PIN__	26

ssize_t _write(int fd, const void *buf, size_t count){
	char *letter = (char *)(buf);
	for (int i = 0; i < count; i++)
	{
		uart_send(*letter);
		letter++;
	}
	return count;
}

int main(){
	uart_init();
	// Configure LED Matrix
	for (int i = 4; i <= 15; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[__BUTTON_A_PIN__] = 0;
	GPIO->PIN_CNF[__BUTTON_B_PIN__] = 0;

	int sleep = 0;
	uint8_t on = 0;
	while (1)
	{
		if(uart_read() != '\0'){
			on = !on;
		}
		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if (on)
		{
			for (int i = 13; i <= 15; i++)
			{
				GPIO->OUTSET = (1 << i);
			}

			for (int i = 4; i <= 12; i++)
			{
				GPIO->OUTCLR = (1 << i);
			}
		}
		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		else if (!on)
		{
			for (int i = 13; i <= 15; i++)
			{
				GPIO->OUTCLR = (1 << i);
			}
			for (int i = 4; i <= 12; i++)
			{
				GPIO->OUTSET = (1 << i);
			}
		}

		if (1 << __BUTTON_A_PIN__ & ~GPIO->IN){
			uart_send('A');
			iprintf("\nThe average grade in TTK%d was in %d and %d: %c\n\r", 4235, 2019, 2018, 'C');
		}

		if (1 << __BUTTON_B_PIN__ & ~GPIO->IN) {
			uart_send('B');
		}

		sleep = 10000;
		while (--sleep);
	}
	return 0;
}