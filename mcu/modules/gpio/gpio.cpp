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




/* ---------------------------------------------------------------------------------------------- */
#include "gpio.hpp"
#include "../../../error/assert.hpp"



/* =================================================================================================
	GPIO
================================================================================================= */

yahal::mcu::modules::Gpio::Port& yahal::mcu::modules::Gpio::operator[](uint8_t portNumber)
{
	return port(portNumber);
}



/* =================================================================================================
	PORT
================================================================================================= */

yahal::mcu::modules::Gpio::Port::Pin yahal::mcu::modules::Gpio::Port::pin(uint8_t pin_number)
{
	yahal::mcu::modules::Gpio::Port::Pin pin(*this, pin_number);
	return pin;
}

yahal::mcu::modules::Gpio::Port::Pin yahal::mcu::modules::Gpio::Port::operator[](uint8_t pin_number)
{
	return pin(pin_number);
}


/* =================================================================================================
	PIN
================================================================================================= */

yahal::mcu::modules::Gpio::Port::Pin::Pin(yahal::mcu::modules::Gpio::Port& port, uint8_t pin_number) :
	port_(port),
	pin_bit_(1<<pin_number) ///< If pin_number greate than 7, then, pin_bit_ = 0x00
{}


bool yahal::mcu::modules::Gpio::Port::Pin::config(Direction::Type direction, Resistor::Type resistor)
{
	return port_.config(direction, resistor, pin_bit_);
}


void yahal::mcu::modules::Gpio::Port::Pin::set(bool b)
{
	port_.set(pin_bit_ & b, pin_bit_);
}


bool yahal::mcu::modules::Gpio::Port::Pin::get() const
{
	return port_.get(pin_bit_);
}


bool yahal::mcu::modules::Gpio::Port::Pin::getOutput() const
{
	return port_.getOutput(pin_bit_);
}


void yahal::mcu::modules::Gpio::Port::Pin::toggle(void)
{
	port_.toggle(pin_bit_);
}


/* ---------------------------------------------------------------------------------------------- */
