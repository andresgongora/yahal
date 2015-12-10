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



#ifndef __MSP430F2132_WDT_HPP_INCLUDED__
#define __MSP430F2132_WDT_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"
#ifdef __MSP430F2132_WDT_ENABLED__

#include "hal/mcu/virtual/wdt/wdt.hpp"



/* ============================================================================================== */
 *	DECLARATION::WDT
 * ============================================================================================== */
class hal::uc::msp430f2132::Wdt : public hal::uc::Wdt
{
public:
				// INITIALIZATION
	bool			init(void);
	void			reset(void);
};


/* ============================================================================================== */
 *	hal::uc::msp430f2132::Wdt :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	extern hal::uc::msp430f2132::Wdt wdt;
}}}

/* ---------------------------------------------------------------------------------------------- */
#endif // __MSP430F2132_WDT_ENABLED__
#endif // __MSP430F2132_WDT_HPP_INCLUDED__
