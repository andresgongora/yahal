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





/* ---------------------------------------------------------------------------------------------- */
#include "wdt.hpp"
#ifdef __MCU_MSP430F5309_WDT_ENABLED__

#include <msp430f5309.h>


/* ============================================================================================== */
 *	DEFINITION::WDT
 * ============================================================================================== */

/** ============================================================================= INITIALIZATION **/

void yahal::mcu::targets::msp430f5309::Wdt::doInit(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
}


void yahal::mcu::targets::msp430f5309::Wdt::reset(void)
{
	init();
}



/* ============================================================================================== */
 *	yahal::mcu::targets::msp430f5309::Wdt :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace yahal{ namespace mcu{
	yahal::mcu::targets::msp430f5309::Wdt wdt;
}

/* ---------------------------------------------------------------------------------------------- */
#endif // __MCU_MSP430F5309_WDT_ENABLED__
