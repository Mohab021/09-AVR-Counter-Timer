
#include <avr/io.h>
#define F_CPU 4000000UL
#include "AVR_Ports.h"
#include "AVR_GPIO_Declarations.h"
#include "AVR_Counter_Timer.h"

int main(void)
{
	int cnt=0;
	Pin_Direction(C, 4, output);
	Pin_Reset(C, 4);

	while(1)
	{
		while( cnt<100 )  //(100 X 20ms = 2 sec)
		{
			T0_delay(); //delay 20 ms
			cnt++;
		}
		
		Pin_Toggle(C, 4); //Toggle LED every 2 seconds
		cnt=0;
	}
}
