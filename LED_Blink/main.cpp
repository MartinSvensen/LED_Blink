#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PB0);  // Sett PB0 som utgang

	while (1)
	{
		PORTB ^= (1 << PB0);  // Bytt mellom høy og lav
		_delay_ms(500);
	}
}