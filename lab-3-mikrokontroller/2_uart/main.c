#include <stdint.h>
#include "gpio.h"

#define __BUTTON_A_PIN__	17
#define __BUTTON_B_PIN__	26

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[__BUTTON_A_PIN__] = 0;
	GPIO->PIN_CNF[__BUTTON_B_PIN__] = 0;

	int sleep = 0;
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if(1 << __BUTTON_B_PIN__ & GPIO->IN){
			for (int i = 4; i < 15; i++)
			{
				GPIO->OUTSET = (1 << i);
			}
			
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if(1 << __BUTTON_A_PIN__ & GPIO->IN){
			for (int i = 4; i < 15; i++)
			{
				GPIO->OUTCLR = (1 << i);
			}
			
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}