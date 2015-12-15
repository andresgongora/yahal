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




#ifndef __YAHAL_MCU_MSP430F5309_WDT_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_WDT_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../msp430f5309_config.hpp"
#ifdef __YAHAL_MCU_MSP430F5309_WDT_ENABLED__

#include "../../../modules/wdt/wdt.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class Wdt;
}}}



/* ============================================================================================== */
 *	DECLARATION::WDT
 * ============================================================================================== */
class yahal::mcu::targets::msp430f5309::Wdt : public yahal::mcu::Wdt
{
private:			// INITIALIZATION
	void			doInit(void);

public:
	void			reset(void);
};



/* ============================================================================================== */
 *	yahal::mcu::targets::msp430f5309::Wdt :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace yahal{ namespace mcu{
	extern yahal::mcu::targets::msp430f5309::Wdt wdt;
}



/* ---------------------------------------------------------------------------------------------- */
#endif // __YAHAL_MCU_MSP430F5309_WDT_ENABLED__
#endif // __YAHAL_MCU_MSP430F5309_WDT_HPP_INCLUDED__
