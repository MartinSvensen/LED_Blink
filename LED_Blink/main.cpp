#include <avr/io.h>

int main()
{
	PORTB &= ~(1 << PB0);  // Sett utgangsverdien til lav
	DDRB  |=  (1 << PB0);  // Konfigurer PB0 som utgang

	while (true)
	{
		// Behold PB0 lav
	}
}