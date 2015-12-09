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



#ifndef __MCU_GPIO_HPP_INCLUDED__
#define __MCU_GPIO_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <stdint.h>
#include "../generic_module.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{
	class Gpio;
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION	mcu::Gpio
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::Gpio : public mcu::GenericModule
{
public:				// CONFIGURATION VALUES --------------------------------------------
				struct DIRECTION{enum type{
					INPUT = false,
					OUTPUT = true
				};};

				struct RESISTOR{enum type{
					DISABLED,
					PULLUP,
					PULLDOWN
				};};

				struct ERROR{enum type{
					NONE = 0,
					TRYING_TO_ACCESS_NON_EXISTANT_PORT,
					TRYING_TO_ACCESS_NON_EXISTANT_PIN,
					COULD_NOT_INITIALIZE_PORT,
					PULLUP_RESISTOR_NOT_AVAILABLE,
					PULLDOWN_RESISTOR_NOT_AVAILABLE,
					OTHER
				};};


public:				// PORT ACCESS -----------------------------------------------------
	class 			Port;
	virtual Port&		port(uint8_t portNumber) = 0;
	Port&			operator[](uint8_t portNumber);
};



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION	mcu::Port
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::Gpio::Port
{

protected:			// CONSTRUCTOR & DESTRUCTOR ----------------------------------------
	virtual			~Port(void){}


public:				// CONFIGURATION ---------------------------------------------------
	virtual bool		config(	DIRECTION::type direction = DIRECTION::INPUT,
					RESISTOR::type resistor = RESISTOR::DISABLED,
					uint8_t mask = 0xFF) = 0;


public:				// CONTROL ---------------------------------------------------------
	virtual void		set(uint8_t value, uint8_t mask=0xFF) = 0;
	virtual uint8_t		get(uint8_t mask=0xFF)const = 0;
	virtual uint8_t		getOutput(uint8_t mask=0xFF)const = 0;
	virtual void		toggle(uint8_t times = 1, uint8_t mask=0xFF);


public:				// PIN ACCESS ------------------------------------------------------
	class 			Pin;
	Pin			pin(uint8_t pinNumber);
	Pin			operator[](uint8_t pinNumber);
};



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION	mcu::Pin
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::Gpio::Port::Pin
{
public:
				// CONSTRUCTOR & COPY ----------------------------------------------
				Pin(mcu::Gpio::Port& port, uint8_t pinNumber);


				// CONFIGURATION ---------------------------------------------------
	bool			config(	DIRECTION::type direction = DIRECTION::INPUT,
					RESISTOR::type resistor = RESISTOR::DISABLED);


				// CONTROL
	void			set(bool b);
	bool			get() const;
	bool			getOutput() const;
	void			toggle(uint8_t times = 1);

private:
				// PRIVATE VARIABLES
	mcu::Gpio::Port&	_port;
	const uint8_t		_pinNumber;
};


/** ============================================================================================ **/
#endif 	//__MCU_GPIO_HPP_INCLUDED__
