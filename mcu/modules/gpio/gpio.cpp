// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015, Individual contributors, see AUTHORS file. 	|
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




/* ---------------------------------------------------------------------------------------------- */
#include "gpio.hpp"
#include "../../../error/assert.hpp"



/* =================================================================================================
	GPIO
================================================================================================= */

yahal::mcu::Gpio::Port& yahal::mcu::Gpio::operator[](uint8_t portNumber)
{
	return port(portNumber);
}



/* =================================================================================================
	PORT
================================================================================================= */

void yahal::mcu::Gpio::Port::toggle(uint8_t mask)
{
	set(~getOutput(), mask);
}


yahal::mcu::Gpio::Port::Pin yahal::mcu::Gpio::Port::pin(uint8_t pinNumber)
{
	assert(pinNumber < 8);
	yahal::mcu::Gpio::Port::Pin pin(*this, pinNumber);
	return pin;
}

yahal::mcu::Gpio::Port::Pin yahal::mcu::Gpio::Port::operator[](uint8_t pinNumber)
{
	return pin(pinNumber);
}


/* =================================================================================================
	PIN
================================================================================================= */

yahal::mcu::Gpio::Port::Pin::Pin(yahal::mcu::Gpio::Port& port, uint8_t pinNumber) :
	port_(port),
	pin_number_(pinNumber)
{}


bool yahal::mcu::Gpio::Port::Pin::config(Direction::Type direction, Resistor::Type resistor)
{
	return port_.config(direction, resistor, (1<<pin_number_));
}


void yahal::mcu::Gpio::Port::Pin::set(bool b)
{
	port_.set((b<<pin_number_), (1<<pin_number_));
}


bool yahal::mcu::Gpio::Port::Pin::get() const
{
	return port_.get((1<<pin_number_));
}


bool yahal::mcu::Gpio::Port::Pin::getOutput() const
{
	return port_.getOutput((1<<pin_number_));
}


void yahal::mcu::Gpio::Port::Pin::toggle(void)
{
	port_.toggle((1<<pin_number_));
}


/* ---------------------------------------------------------------------------------------------- */
