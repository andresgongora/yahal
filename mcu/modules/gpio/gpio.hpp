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

#ifndef __YAHAL_MCU_MODULES_GPIO_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_GPIO_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include "../base_module.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{
	class Gpio;
}}}



/***********************************************************************************************//**
 * Base class for GPIO modules.
 **************************************************************************************************/
class yahal::mcu::modules::Gpio
{
public:
				/// Direction of GPIO pins
				struct Direction{enum Type{
					INPUT = false,
					OUTPUT = true
				};}static const DIRECTION;

				/// Pull-up and pull-down resistor configuration
				struct Resistor{enum Type{
					DISABLED,
					PULLUP,
					PULLDOWN
				};} static const RESISTOR;

				// -----------------------------------------------------------------
public:
	class 			Port;

				/// Return reference to port.
	virtual Port&		port(uint8_t portNumber) = 0;

				/// Short wrapper for port(uint8_t portNumber).
				/// @see port(uint8_t portNumber).
	Port&			operator[](uint8_t portNumber);
};



/***********************************************************************************************//**
 * Base class for all GPIO Ports.
 * Declared inside Gpio.
 **************************************************************************************************/
class yahal::mcu::modules::Gpio::Port
{
protected:
				/// This is a base class.
				Port(void) {}


public:				// CONFIGURATION
	virtual bool		config(	Direction::Type direction = Direction::INPUT,
					Resistor::Type resistor = Resistor::DISABLED,
					uint8_t mask = 0xFF) = 0;


				// CONTROL
	virtual void		set(uint8_t value, uint8_t mask=0xFF) = 0;
	virtual uint8_t		get(uint8_t mask=0xFF)const = 0;
	virtual uint8_t		getOutput(uint8_t mask=0xFF)const = 0;
	virtual void		toggle(uint8_t mask=0xFF) = 0;


public:				// PIN ACCESS
	class 			Pin;
	Pin			pin(uint8_t pin_number);
	Pin			operator[](uint8_t pin_number);
};



/***********************************************************************************************//**
 * Base class for all GPIO Pins.
 * Declared inside Gpio::Port
 **************************************************************************************************/
class yahal::mcu::modules::Gpio::Port::Pin
{
public:
				Pin(yahal::mcu::modules::Gpio::Port& port, uint8_t pin_number);


				// CONFIGURATION
	bool			config(	Direction::Type direction = Direction::INPUT,
					Resistor::Type resistor = Resistor::DISABLED);


				// CONTROL
	void			set(bool b);
	bool			get() const;
	bool			getOutput() const;
	void			toggle(void);

private:
				// PRIVATE VARIABLES
	Gpio::Port&		port_;
	const uint8_t		pin_bit_;
};


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_GPIO_HPP_INCLUDED__
