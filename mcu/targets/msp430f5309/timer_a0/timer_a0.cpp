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

#include "timer_a0.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>
#include "../../../../error/assert.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::TimerA0::TimerA0(const Configuration& configuration) :
	configuration_(configuration)
{}



void yahal::mcu::targets::msp430f5309::TimerA0::doInit(void)
{

}

/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr& \
yahal::mcu::targets::msp430f5309::TimerA0::ccr(std::size_t module)
{
	switch (module) {
	case 1:
		return ccr1_;
	case 2:
		return ccr2_;
	case 3:
		return ccr3_;
	case 4:
		return ccr4_;
	case 5:
		return ccr5_;
	case 6:
		return ccr6_;
	default:assert(false);
		return ccr1_;	///< Better return this than nothing.
	}
}


/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
