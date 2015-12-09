// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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




/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "gpio.hpp"



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::Gpio
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/


mcu::Gpio::Port& mcu::Gpio::operator[](uint8_t portNumber)
{
	return port(portNumber);
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::Gpio::Port
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

void mcu::Gpio::Port::toggle(uint8_t times, uint8_t mask)
{
	for(; times; times--)
	{
		set(~getOutput(), mask);
	}
}


mcu::Gpio::Port::Pin mcu::Gpio::Port::pin(uint8_t pinNumber)
{
	if(pinNumber >= 8)
	{
		for(;;);	//TODO:: trap
	}


	mcu::Gpio::Port::Pin pin(*this, pinNumber);
	return pin;
}


mcu::Gpio::Port::Pin mcu::Gpio::Port::operator[](uint8_t pinNumber)
{
	return pin(pinNumber);
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::Gpio::Port::Pin
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

mcu::Gpio::Port::Pin::Pin(mcu::Gpio::Port& port, uint8_t pinNumber) :
	_port(port),
	_pinNumber(pinNumber)
{}


bool mcu::Gpio::Port::Pin::config(DIRECTION::type direction, RESISTOR::type resistor)
{
	return _port.config(direction, resistor, (1<<_pinNumber));
}


void mcu::Gpio::Port::Pin::set(bool b)
{
	_port.set((b<<_pinNumber), (1<<_pinNumber));
}


bool mcu::Gpio::Port::Pin::get() const
{
	return _port.get((1<<_pinNumber));
}


bool mcu::Gpio::Port::Pin::getOutput() const
{
	return _port.getOutput((1<<_pinNumber));
}


void mcu::Gpio::Port::Pin::toggle(uint8_t times)
{
	_port.toggle(times, (1<<_pinNumber));
}


/** ============================================================================================ **/
