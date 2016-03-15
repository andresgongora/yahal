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
#include "../modules_namespace.hpp"



/***********************************************************************************************//**
 * Base class for GPIO modules.
 **************************************************************************************************/
class yahal::mcu::modules::Gpio : public yahal::mcu::modules::details::BaseModule
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
	inline Port&		operator[](uint8_t portNumber)	{return port(portNumber);}
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


				// PIN ACCESS
	class 			Pin;
	inline Pin		pin(uint8_t pin_number);
	inline Pin		operator[](uint8_t pin_number);
};



/***********************************************************************************************//**
 * Base class for all GPIO Pins.
 * Declared inside Gpio::Port
 **************************************************************************************************/
class yahal::mcu::modules::Gpio::Port::Pin
{
public:
	explicit		Pin(yahal::mcu::modules::Gpio::Port& port, uint8_t pin_number):
					port_(port),
					pin_bit_(1<<pin_number) ///< If pin_number greate than 7, then, pin_bit_ = 0x00
				{}


				// CONFIGURATION
	inline bool		config(	Direction::Type direction = Direction::INPUT,
					Resistor::Type resistor = Resistor::DISABLED);


				// CONTROL
	inline void		set(bool b);
	inline bool		get(void) const;
	inline bool		getOutput(void) const;
	inline void		toggle(void);

private:
				// PRIVATE VARIABLES
	Gpio::Port&		port_;
	const uint8_t		pin_bit_;
};



/* =================================================================================================
	PORT INLINE FUNCTIONS
================================================================================================= */

inline yahal::mcu::modules::Gpio::Port::Pin yahal::mcu::modules::Gpio::Port::pin(uint8_t pin_number)
{
	return yahal::mcu::modules::Gpio::Port::Pin(*this, pin_number);
}


inline  yahal::mcu::modules::Gpio::Port::Pin yahal::mcu::modules::Gpio::Port::operator[](uint8_t pin_number)
{
	return pin(pin_number);
}



/* =================================================================================================
	PIN INLINE FUNCTIONS
================================================================================================= */

inline bool yahal::mcu::modules::Gpio::Port::Pin::config(Direction::Type direction,
							 Resistor::Type resistor)
{
	return port_.config(direction, resistor, pin_bit_);
}


inline void yahal::mcu::modules::Gpio::Port::Pin::set(bool b)
{
	port_.set(pin_bit_ & b, pin_bit_);
}


inline bool yahal::mcu::modules::Gpio::Port::Pin::get(void) const
{
	return port_.get(pin_bit_);
}


inline bool yahal::mcu::modules::Gpio::Port::Pin::getOutput(void) const
{
	return port_.getOutput(pin_bit_);
}


inline void yahal::mcu::modules::Gpio::Port::Pin::toggle(void)
{
	port_.toggle(pin_bit_);
}



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_GPIO_HPP_INCLUDED__
