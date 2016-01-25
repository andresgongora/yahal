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
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../config/targets/msp430f5309/config.hpp"
#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true

#include "../../../config/targets/msp430f5309/gpio.hpp"

#include <msp430f5309.h>
#include "../../../../error/assert.hpp"
#include "../../empty/gpio/gpio.hpp"


/* =================================================================================================
	GPIO
================================================================================================= */

/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::Gpio	\
yahal::mcu::targets::msp430f5309::Gpio::instance_(yahal::mcu::targets::msp430f5309::config::gpio);


yahal::mcu::targets::msp430f5309::Gpio& yahal::mcu::targets::msp430f5309::Gpio::getInstance(void)
{
	return instance_;
}



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::Gpio::Gpio(const Configuration& configuration) :
	configuration_(configuration)
{}



bool yahal::mcu::targets::msp430f5309::Gpio::init(void)
{
	bool success = true;

	P1OUT = P2OUT = P3OUT = P4OUT = P5OUT = P6OUT = 0;	// Clear outputs

	success &= Port1::getInstance().config(Direction::INPUT, Resistor::DISABLED);
	success &= Port2::getInstance().config(Direction::INPUT, Resistor::DISABLED);
	success &= Port3::getInstance().config(Direction::INPUT, Resistor::DISABLED);
	success &= Port4::getInstance().config(Direction::INPUT, Resistor::DISABLED);
	success &= Port5::getInstance().config(Direction::INPUT, Resistor::DISABLED);
	success &= Port6::getInstance().config(Direction::INPUT, Resistor::DISABLED);

	return success;
}


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

yahal::mcu::targets::msp430f5309::Gpio::Port1
yahal::mcu::targets::msp430f5309::Gpio::Port1::instance_;


yahal::mcu::targets::msp430f5309::Gpio::Port1&
yahal::mcu::targets::msp430f5309::Gpio::Port1::getInstance(void)
{
	return instance_;
}


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
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P1OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P1OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port1::get(uint8_t mask)const {return P1IN & mask;}
uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port1::getOutput(uint8_t mask)const {return P1OUT & mask;}



/* =================================================================================================
	PORT 2
================================================================================================= */

yahal::mcu::targets::msp430f5309::Gpio::Port2
yahal::mcu::targets::msp430f5309::Gpio::Port2::instance_;


yahal::mcu::targets::msp430f5309::Gpio::Port2&
yahal::mcu::targets::msp430f5309::Gpio::Port2::getInstance(void)
{
	return instance_;
}


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
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P2OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P2OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port2::get(uint8_t mask)const {return P2IN & mask;}
uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port2::getOutput(uint8_t mask)const {return P2OUT & mask;}



/* =================================================================================================
	PORT 3
================================================================================================= */

yahal::mcu::targets::msp430f5309::Gpio::Port3
yahal::mcu::targets::msp430f5309::Gpio::Port3::instance_;


yahal::mcu::targets::msp430f5309::Gpio::Port3&
yahal::mcu::targets::msp430f5309::Gpio::Port3::getInstance(void)
{
	return instance_;
}


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
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P3OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P3OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port3::get(uint8_t mask)const {return P3IN & mask;}
uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port3::getOutput(uint8_t mask)const {return P3OUT & mask;}



/* =================================================================================================
	PORT 4
================================================================================================= */

yahal::mcu::targets::msp430f5309::Gpio::Port4
yahal::mcu::targets::msp430f5309::Gpio::Port4::instance_;


yahal::mcu::targets::msp430f5309::Gpio::Port4&
yahal::mcu::targets::msp430f5309::Gpio::Port4::getInstance(void)
{
	return instance_;
}


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
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P4OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P4OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port4::get(uint8_t mask)const {return P4IN & mask;}
uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port4::getOutput(uint8_t mask)const {return P4OUT & mask;}



/* =================================================================================================
	PORT 5
================================================================================================= */

yahal::mcu::targets::msp430f5309::Gpio::Port5
yahal::mcu::targets::msp430f5309::Gpio::Port5::instance_;


yahal::mcu::targets::msp430f5309::Gpio::Port5&
yahal::mcu::targets::msp430f5309::Gpio::Port5::getInstance(void)
{
	return instance_;
}


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
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P5OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P5OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port5::get(uint8_t mask)const {return P5IN & mask;}
uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port5::getOutput(uint8_t mask)const {return P5OUT & mask;}



/* =================================================================================================
	PORT 6
================================================================================================= */

yahal::mcu::targets::msp430f5309::Gpio::Port6
yahal::mcu::targets::msp430f5309::Gpio::Port6::instance_;


yahal::mcu::targets::msp430f5309::Gpio::Port6&
yahal::mcu::targets::msp430f5309::Gpio::Port6::getInstance(void)
{
	return instance_;
}


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
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P6OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P6OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port6::get(uint8_t mask)const {return P6IN & mask;}
uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port6::getOutput(uint8_t mask)const {return P6OUT & mask;}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
