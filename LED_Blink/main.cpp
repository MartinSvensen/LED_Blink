#include <avr/io.h>
#include <avr/interrupt.h>

ISR(PCINT2_vect)
{
	// Reager bare når knappen er trykket, ikke ved slipp
	if ((PIND & (1 << PD2)) == 0)
	{
		PORTD ^= (1 << PD6);  // Bytt LED-tilstand
	}
}

int main()
{
	// LED: PD6 som utgang, starter avslått
	PORTD &= ~(1 << PD6);
	DDRD |= (1 << PD6);

	// Knapp: PD2 som inngang med pull-up
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);

	// PD2 har pin change-navnet PCINT18
	PCMSK2 |= (1 << PCINT18); // Velg PD2
	PCIFR = (1 << PCIF2);     // Slett eventuelt ventende flagg
	PCICR |= (1 << PCIE2);    // Aktiver gruppen for port D

	sei();                    // Tillat avbrudd globalt

	while (true)
	{
		// Knappen håndteres av avbruddsrutinen
	}
}