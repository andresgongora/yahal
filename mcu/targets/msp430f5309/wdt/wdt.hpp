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

#ifndef __YAHAL_MCU_MSP430F5309_WDT_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_WDT_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../msp430f5309_namespace.hpp"
#include "../../../modules/wdt/wdt.hpp"
#include "../../../../utility/oop/singleton.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Wdt :
	public yahal::mcu::modules::Wdt,
	public yahal::utility::oop::Singleton<yahal::mcu::targets::msp430f5309::Wdt>
{
public:
				Wdt(void);
	virtual void		reset(void);		///< Reset WDT counter (if enabled)


};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_MSP430F5309_WDT_HPP_INCLUDED__
