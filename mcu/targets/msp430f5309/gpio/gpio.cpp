// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file.	|
	| 									|
	| This program is free software: you can redistribute it and/or modify	|
	| it under the terms of the GNU General Public License as published by	|
	| the Free Software Foundation, either version 2 of the License, or	|
	| (at your option) any later version.					|
	|									|
	| This program is distributed in the hope that it will be useful,	|
	| but WITHOUT ANY WARRANTY; without even the implied warranty of	|
	| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		|
	| GNU General Public License for more details.				|
	|									|
	| You should have received a copy of the GNU General Public License	|
	| along with this program.  If not, see <http://www.gnu.org/licenses/>. |
	|									|
	+-----------------------------------------------------------------------+	*/

#include "gpio.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_GPIO

#include <msp430f5309.h>
#include "../../../../error/assert.hpp"
#include "../../empty/gpio/gpio.hpp"
#include "../../../../utility/data/mask.hpp"


/* =================================================================================================
	GPIO
================================================================================================= */

yahal::mcu::targets::msp430f5309::Gpio::Gpio(void)
{}


yahal::mcu::modules::Gpio::Port& yahal::mcu::targets::msp430f5309::Gpio::port(uint8_t portNumber)
{
	assert(portNumber >= 1 && portNumber <= 6);

	switch(portNumber)
	{
	case 1:	return Port1::getInstance();
	case 2:	return Port2::getInstance();
	case 3:	return Port3::getInstance();
	case 4:	return Port4::getInstance();
	case 5:	return Port5::getInstance();
	case 6:	return Port6::getInstance();

	default:
		static yahal::mcu::targets::empty::Gpio::EmptyPort empty_port;
		return empty_port;	///< Better return this than nothing.
	}
}



/* =================================================================================================
	PORT 1
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::Gpio::Port1::config(Direction::Type direction,
							   Resistor::Type resistor,
							   uint8_t mask) {
	// WRITE CONFIGURATION
	P1SEL &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P1DIR = (direction == Direction::OUTPUT ? P1DIR | mask : P1DIR & (~mask));

	// RESISTOR
	if (resistor == Resistor::PULLUP && direction == Direction::INPUT) {
		P1REN |= mask;		// Enable resistor
		P1OUT |= mask; 		// Configure as pullup
	} else if (resistor == Resistor::PULLDOWN && direction == Direction::INPUT) {
		P1REN |= mask;		// Enable resistor
		P1OUT &= (~mask);	// Configure as pulldown
	} else {
		P1REN &= ~mask;		// Disable resistor
	}

	return true;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port1::set(uint8_t value, uint8_t mask)
{
	yahal::utility::data::setMasked(P1OUT, value, mask);
}

void  yahal::mcu::targets::msp430f5309::Gpio::Port1::toggle(uint8_t mask)
{
	P1OUT ^= mask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port1::get(uint8_t mask)const
{
	return P1IN & mask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port1::getOutput(uint8_t mask)const
{
	return P1OUT & mask;
}



/* =================================================================================================
	PORT 2
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::Gpio::Port2::config(Direction::Type direction,
							   Resistor::Type resistor,
							   uint8_t mask)
{
	// WRITE CONFIGURATION
	P2SEL &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P2DIR = (direction == Direction::OUTPUT ? P2DIR | mask : P2DIR & (~mask));

	// RESISTOR
	if (resistor == Resistor::PULLUP && direction == Direction::INPUT) {
		P2REN |= mask;		// Enable resistor
		P2OUT |= mask; 		// Configure as pullup
	} else if (resistor == Resistor::PULLDOWN && direction == Direction::INPUT) {
		P2REN |= mask;		// Enable resistor
		P2OUT &= (~mask);	// Configure as pulldown
	} else {
		P2REN &= ~mask;		// Disable resistor
	}

	return true;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port2::set(uint8_t value, uint8_t mask)
{
	yahal::utility::data::setMasked(P2OUT, value, mask);
}

void  yahal::mcu::targets::msp430f5309::Gpio::Port2::toggle(uint8_t mask)
{
	P2OUT ^= mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port2::get(uint8_t mask) const
{
	return P2IN & mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port2::getOutput(uint8_t mask) const
{
	return P2OUT & mask;
}



/* =================================================================================================
	PORT 3
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::Gpio::Port3::config(Direction::Type direction,
							   Resistor::Type resistor,
							   uint8_t mask)
{
	// WRITE CONFIGURATION
	P3SEL &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P3DIR = (direction == Direction::OUTPUT ? P3DIR | mask : P3DIR & (~mask));

	// RESISTOR
	if (resistor == Resistor::PULLUP && direction == Direction::INPUT) {
		P3REN |= mask;		// Enable resistor
		P3OUT |= mask; 		// Configure as pullup
	} else if (resistor == Resistor::PULLDOWN && direction == Direction::INPUT) {
		P3REN |= mask;		// Enable resistor
		P3OUT &= (~mask);	// Configure as pulldown
	} else {
		P3REN &= ~mask;		// Disable resistor
	}

	return true;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port3::set(uint8_t value, uint8_t mask)
{
	yahal::utility::data::setMasked(P3OUT, value, mask);
}

void  yahal::mcu::targets::msp430f5309::Gpio::Port3::toggle(uint8_t mask)
{
	P3OUT ^= mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port3::get(uint8_t mask) const
{
	return P3IN & mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port3::getOutput(uint8_t mask) const
{
	return P3OUT & mask;
}



/* =================================================================================================
	PORT 4
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::Gpio::Port4::config(Direction::Type direction,
							   Resistor::Type resistor,
							   uint8_t mask)
{
	// WRITE CONFIGURATION
	P4SEL &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P4DIR = (direction == Direction::OUTPUT ? P4DIR | mask : P4DIR & (~mask));

	// RESISTOR
	if (resistor == Resistor::PULLUP && direction == Direction::INPUT) {
		P4REN |= mask;		// Enable resistor
		P4OUT |= mask; 		// Configure as pullup
	} else if (resistor == Resistor::PULLDOWN && direction == Direction::INPUT) {
		P4REN |= mask;		// Enable resistor
		P4OUT &= (~mask);	// Configure as pulldown
	} else {
		P4REN &= ~mask;		// Disable resistor
	}

	return true;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port4::set(uint8_t value, uint8_t mask)
{
	yahal::utility::data::setMasked(P4OUT, value, mask);
}

void  yahal::mcu::targets::msp430f5309::Gpio::Port4::toggle(uint8_t mask)
{
	P4OUT ^= mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port4::get(uint8_t mask) const
{
	return P4IN & mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port4::getOutput(uint8_t mask) const
{
	return P4OUT & mask;
}



/* =================================================================================================
	PORT 5
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::Gpio::Port5::config(Direction::Type direction,
							   Resistor::Type resistor,
							   uint8_t mask)
{
	// WRITE CONFIGURATION
	P5SEL &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P5DIR = (direction == Direction::OUTPUT ? P5DIR | mask : P5DIR & (~mask));

	// RESISTOR
	if (resistor == Resistor::PULLUP && direction == Direction::INPUT) {
		P5REN |= mask;		// Enable resistor
		P5OUT |= mask; 		// Configure as pullup
	} else if (resistor == Resistor::PULLDOWN && direction == Direction::INPUT) {
		P5REN |= mask;		// Enable resistor
		P5OUT &= (~mask);	// Configure as pulldown
	} else {
		P5REN &= ~mask;		// Disable resistor
	}

	return true;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port5::set(uint8_t value, uint8_t mask)
{
	yahal::utility::data::setMasked(P5OUT, value, mask);
}

void  yahal::mcu::targets::msp430f5309::Gpio::Port5::toggle(uint8_t mask)
{
	P5OUT ^= mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port5::get(uint8_t mask) const
{
	return P5IN & mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port5::getOutput(uint8_t mask) const
{
	return P5OUT & mask;
}



/* =================================================================================================
	PORT 6
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::Gpio::Port6::config(Direction::Type direction,
							   Resistor::Type resistor,
							   uint8_t mask)
{
	// WRITE CONFIGURATION
	P6SEL &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P6DIR = (direction == Direction::OUTPUT ? P6DIR | mask : P6DIR & (~mask));

	// RESISTOR
	if (resistor == Resistor::PULLUP && direction == Direction::INPUT) {
		P6REN |= mask;		// Enable resistor
		P6OUT |= mask; 		// Configure as pullup
	} else if (resistor == Resistor::PULLDOWN && direction == Direction::INPUT) {
		P6REN |= mask;		// Enable resistor
		P6OUT &= (~mask);	// Configure as pulldown
	} else {
		P6REN &= ~mask;		// Disable resistor
	}

	return true;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port6::set(uint8_t value, uint8_t mask)
{
	yahal::utility::data::setMasked(P6OUT, value, mask);
}

void  yahal::mcu::targets::msp430f5309::Gpio::Port6::toggle(uint8_t mask)
{
	P6OUT ^= mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port6::get(uint8_t mask) const
{
	return P6IN & mask;
}

uint8_t yahal::mcu::targets::msp430f5309::Gpio::Port6::getOutput(uint8_t mask) const
{
	return P6OUT & mask;
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_GPIO
