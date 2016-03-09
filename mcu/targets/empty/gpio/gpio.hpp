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

#ifndef __YAHAL_MCU_EMPTY_GPIO_HPP_INCLUDED__
#define __YAHAL_MCU_EMPTY_GPIO_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../modules/gpio/gpio.hpp"
#include "../empty_namespace.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::empty::Gpio : public yahal::mcu::modules::Gpio
{
public:
				class EmptyPort : public yahal::mcu::modules::Gpio::Port
				{
				public:
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF) {return true;}

					virtual void	set(uint8_t value, uint8_t mask=0xFF) {}
					virtual void	toggle(uint8_t mask=0xFF) {}
					virtual uint8_t	get(uint8_t mask=0xFF)const {return false;}
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const {return false;}

				};


	virtual Port& 		port(uint8_t portNumber){return empty_port;}

private:
	EmptyPort		empty_port;
};



/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_MCU_MSP430F5309_GPIO_HPP_INCLUDED__
