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

#ifndef __YAHAL_MCU_TARGETS_EMPTY_PORT_HPP_INCLUDED__
#define __YAHAL_MCU_TARGETS_EMPTY_PORT_HPP_INCLUDED__


#include "../empty_namespace.hpp"
#include "../../../modules/gpio/port.hpp"
#include "../../../../cool/src/pattern/creational/singleton.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::empty::Port : public yahal::mcu::modules::Port
{
public:
				class Pin : public yahal::mcu::modules::Port::Pin
				{
				public:
					virtual void	setAsInput(void) {}
					virtual void 	setAsOutput(void) {}
					virtual void	set(bool b) {}
					virtual bool	get(void) const {return false;}
					virtual void	toggle(void) {}
				};
				//----------------------------------------------------------
public:
	virtual void		setAsInput(uint8_t mask = 0xFF) {}
	virtual void		setAsOutput(uint8_t mask = 0xFF) {}
	virtual void		set(uint8_t value, uint8_t mask=0xFF) {}
	virtual void		toggle(uint8_t mask=0xFF) {}
	virtual uint8_t		get(uint8_t mask=0xFF)const {return false;}

	virtual Pin&		pin(uint8_t pin_number) {return empty_pin_;}

private:
	Pin			empty_pin_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_MCU_TARGETS_EMPTY_PORT_HPP_INCLUDED__
