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



#ifndef __YAHAL_MCU_GPIO_HPP_INCLUDED__
#define __YAHAL_MCU_GPIO_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include "../base_module.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	class Gpio;
}}



/***********************************************************************************************//**
 * Base class for GPIO modules.
 **************************************************************************************************/
class yahal::mcu::Gpio :
		public yahal::mcu::details::BaseModule
{
public:
				/**
				 * Direction of GPIO pins
				 */
				struct Direction{enum Type{
					INPUT = false,
					OUTPUT = true
				};};


				/**
				 * Pull-up and pull-down resistor configuration
				 */
				struct Resistor{enum Type{
					DISABLED,
					PULLUP,
					PULLDOWN
				};};

				/**
				 * GPIO errors
				 */
				struct Error{enum Type{
					NO_ERROR = 0,
					TRYING_TO_ACCESS_NON_EXISTANT_PORT,
					TRYING_TO_ACCESS_NON_EXISTANT_PIN,
					COULD_NOT_INITIALIZE_PORT,
					PULLUP_Resistor_NOT_AVAILABLE,
					PULLDOWN_Resistor_NOT_AVAILABLE,
					OTHER
				};};


public:				// PORT ACCESS
	class 			Port;

				/**
				 * Return reference to port.
				 */
	virtual Port&		port(uint8_t portNumber) = 0;

				/**
				 * Short wrapper for port(uint8_t portNumber).
				 * @see port(uint8_t portNumber).
				 */
	Port&			operator[](uint8_t portNumber);
};



/***********************************************************************************************//**
 * Base class for all GPIO Ports.
 * Declared inside Gpio.
 **************************************************************************************************/
class yahal::mcu::Gpio::Port
{
public:				// CONFIGURATION ---------------------------------------------------
	virtual bool		config(	Direction::Type direction = Direction::INPUT,
					Resistor::Type resistor = Resistor::DISABLED,
					uint8_t mask = 0xFF) = 0;


public:				// CONTROL ---------------------------------------------------------
	virtual void		set(uint8_t value, uint8_t mask=0xFF) = 0;
	virtual uint8_t		get(uint8_t mask=0xFF)const = 0;
	virtual uint8_t		getOutput(uint8_t mask=0xFF)const = 0;
	virtual void		toggle(uint8_t mask=0xFF);


public:				// PIN ACCESS ------------------------------------------------------
	class 			Pin;
	Pin			pin(uint8_t pinNumber);
	Pin			operator[](uint8_t pinNumber);
};



/***********************************************************************************************//**
 * Base class for all GPIO Pins.
 * Declared inside Gpio::Port
 **************************************************************************************************/
class yahal::mcu::Gpio::Port::Pin
{
public:
				// CONSTRUCTOR & COPY ----------------------------------------------
				Pin(yahal::mcu::Gpio::Port& port, uint8_t pinNumber);


				// CONFIGURATION ---------------------------------------------------
	bool			config(	Direction::Type direction = Direction::INPUT,
					Resistor::Type resistor = Resistor::DISABLED);


				// CONTROL
	void			set(bool b);
	bool			get() const;
	bool			getOutput() const;
	void			toggle(void);

private:
				// PRIVATE VARIABLES
	yahal::mcu::Gpio::Port&	_port;
	const uint8_t		_pinNumber;
};


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_GPIO_HPP_INCLUDED__
