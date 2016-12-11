/*
 * Driver.cpp
 *
 * Created: 10.12.2016 20:42:19
 * Author : Developer
 */ 

 #define F_CPU 8000000UL

#include <avr/io.h>
#include  <util/delay.h>

#include <stdint.h>

#define DELAY 500


#define ON(port, target) port |= (1 << target)
#define OFF(port, target) port &= ~(1 << target)

void impulse(volatile uint8_t* t_port, int target) {

	volatile uint8_t* port = (t_port + 0x01);

	ON(*port, target);

	_delay_us(DELAY);

	OFF(*port, target);

}

int main(void) {
    DDRD |= (1 << DDD1) | (1 << DDD2) | (1 << DDD3) | (1 << DDD4);

	int reverser = 0;
	int port = 1;
    while (1) {
		impulse(&DDRD, port);

		if (reverser < 1000) {
			port++;
			if (port > 4) port = 1;
		} else {
			port--;
			if (port < 1) port = 4;

			if (reverser > 2000) reverser = 0;
		}

		reverser++;
    }
}

