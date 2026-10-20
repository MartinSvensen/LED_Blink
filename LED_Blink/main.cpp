#include <avr/io.h>
#include <avr/interrupt.h>

bool stablePressed = false;     // Godkjent knappetilstand
uint8_t differentSamples = 0;   // Avlesninger ulik godkjent tilstand

ISR(TIMER1_COMPA_vect)
{
	bool pressed = (PIND & (1 << PD2)) == 0;

	if (pressed == stablePressed)
	{
		// Tilbake til godkjent tilstand: start tellingen på nytt
		differentSamples = 0;
	}
	else
	{
		++differentSamples;

		if (differentSamples >= 20)
		{
			// Ny tilstand har vart i omtrent 20 ms
			stablePressed = pressed;
			differentSamples = 0;

			if (stablePressed)
			{
				PORTD ^= (1 << PD6); // Bytt bare ved godkjent trykk
			}
		}
	}
}

int main()
{
	// LED på PD6, starter avslått
	PORTD &= ~(1 << PD6);
	DDRD |= (1 << PD6);

	// Knapp på PD2 med pull-up
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);

	// Bruk timeravbrudd i stedet for pin change
	PCICR &= ~(1 << PCIE2);

	// Timer1: CTC-modus, ett avbrudd hvert 1 ms ved 1 MHz
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 124;

	TIFR1 = (1 << OCF1A);    // Slett eventuelt ventende flagg
	TIMSK1 = (1 << OCIE1A);  // Aktiver compare match A-avbrudd
	TCCR1B = (1 << WGM12) | (1 << CS11); // CTC, prescaler 8

	sei();

	while (true)
	{
	}
}