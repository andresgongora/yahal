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





#ifndef __YAHAL_MCU_WDT_HPP_INCLUDED__
#define __YAHAL_MCU_WDT_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include "../base_module.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{
	class Wdt;
}}}




/***********************************************************************************************//**
 * @brief	Base class for all Watch Dog Timers.
 **************************************************************************************************/
class yahal::mcu::modules::Wdt : public yahal::mcu::modules::details::BaseModule
{
public:
				struct Error {enum Type {
					NO_ERROR = 0,
					OTHER
				};};


protected:
				Wdt(void) {}

public:
				/**
				 * Reset watch dog timer count.
				 */
	virtual void		reset(void) = 0;
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_WDT_HPP_INCLUDED__
