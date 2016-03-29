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

#ifndef __YAHAL_MCU_MODULES_ISR_HANDLER_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_ISR_HANDLER_HPP_INCLUDED__


#include <stdint.h>
#include "../modules_namespace.hpp"



/***********************************************************************************************//**
 * @brief	Base class for all ISR handlers.
 **************************************************************************************************/
class yahal::mcu::modules::details::IsrHandler
{
public:
	virtual void isr(uint8_t) = 0;
protected:
	virtual void enableIrq(void) = 0;
	virtual void disableIrq(void) = 0;
public:
	class Empty;
};



/***********************************************************************************************//**
 * @brief	IsrHandler empty derived
 **************************************************************************************************/
class yahal::mcu::modules::details::IsrHandler::Empty :
	public yahal::mcu::modules::details::IsrHandler
{
public:
	virtual void isr(uint8_t)	{}
private:
	virtual void enableIrq(void)	{}
	virtual void disableIrq(void)	{}
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_ISR_HANDLER_HPP_INCLUDED__