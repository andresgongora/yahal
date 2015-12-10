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
#include <mcu/targets/msp430f2132/wdt/wdt.hpp>
#include <msp430f2132.h>

#ifdef __MSP430F2132_WDT_ENABLED__



/* ============================================================================================== */
 *	DEFINITION::WDT
 * ============================================================================================== */

/** ============================================================================= INITIALIZATION **/

bool hal::uc::msp430f2132::Wdt::init(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	setInitialized();	// Mark module as initialized
	return true;
}


void hal::uc::msp430f2132::Wdt::reset(void)
{
	init();
}



/* ============================================================================================== */
 *	hal::uc::msp430f2132::Wdt :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	hal::uc::msp430f2132::Wdt wdt;
}}}

/* ---------------------------------------------------------------------------------------------- */
#endif // __MSP430F2132_WDT_ENABLED__
