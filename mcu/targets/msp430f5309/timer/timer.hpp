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




#ifndef __MCU_M430F5309_TIMER_HPP_INCLUDED__
#define __MCU_M430F5309_TIMER_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../msp430f5309.hpp"
#ifdef __MCU_MSP430F5309_TIMER_ENABLED__

#include <stdint.h>




/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class TimerA;
}}}



/* ============================================================================================== */
 *	GPIO
 * ============================================================================================== */
class yahal::mcu::targets::msp430f5309::TimerA
{
public:




};



/* ============================================================================================== */
 *	yahal::mcu::targets::msp430f5309::Gpio :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f5309{
	extern yahal::mcu::targets::msp430f5309::TimerA timerA;
}}}



/* ---------------------------------------------------------------------------------------------- */
#endif // __MCU_MSP430F5309_TIMER_ENABLED__
#endif // __MCU_MSP430F5309_TIMER_HPP_INCLUDED__
