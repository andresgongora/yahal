// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015 - 2016 - 2016, Individual contributors, see AUTHORS file. |
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

#ifndef __YAHAL_MCU_MODULES_TIMER_16_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_TIMER_16_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include "../base_module.hpp"
#include "../../../utility/oop/publish_subscribe.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{
	class Timer16;
}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::modules::Timer16 :
	public yahal::mcu::modules::details::BaseModule,
	public yahal::utility::oop::Publisher<int>
{
public:
				struct Event { enum Type {
					OVERFLOW,
					PERIOD,
				};};

				// -----------------------------------------------------------------
public:
	virtual void		setCount(uint16_t count) = 0;
	virtual uint16_t	getCount(void) const = 0;
	virtual void		setPeriod(uint16_t period) = 0;
	virtual void		reset(void) = 0;
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_TIMER_16_HPP_INCLUDED__
