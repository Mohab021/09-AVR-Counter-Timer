
#include <avr/io.h>
#define F_CPU 4000000UL
#include "AVR_Counter_Timer.h"

void T0_delay()
{
	/*using Timer0, gives us 256 cycles before overflowing
	we want to make a timer of 20 ms
	using 4MHz cpu_f, Fosc = 4MHz
	using a pre-scalar of 1024, then Fosc_new = 3906.25 Hz
	time of one cycle = 1 / 3906.25 = 0.256 ms
	number of cycles to get 10ms delay, = (20ms / 0.256ms) = 78 cycles (approx)
	(256 - 78) = 178 cycles, then we have to start counting from [[178]]
	to get overflow after 78 cycles (20 ms)
	178 = 0b10110010 = 0xB2 (using decimal to hex or binary converter)
	*/
	
	TCCR0 =0x05;  //0b00000101 = 0x05, using Normal mode, pre-scalar of 1024 (Counter Control Register)
	TCNT0 = 0xB2; //start with 178 (Counter Register)

	while( !(TIFR & (1<<TOV0)) ) ; //wait until TOV0 becomes 1, then overflow happens (counting process happens here)

	TCCR0 = 0x00; //stop the counter [No clock source]
	TIFR |= (1<<TOV0); //clear TOV0 again by writing [[1]] not 0, TIFR = 0bXXXXXXX1
}