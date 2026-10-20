#include <avr/io.h>

int main()
{
	// LED: PD6 som utgang, starter avslått
	PORTD &= ~(1 << PD6);
	DDRD |= (1 << PD6);

	// Knapp: PD2 som inngang med intern pull-up
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);

	while (true)
	{
		if ((PIND & (1 << PD2)) == 0)
		{
			PORTD |= (1 << PD6);   // Tenn LED
		}
		else
		{
			PORTD &= ~(1 << PD6);  // Slukk LED
		}
	}
}