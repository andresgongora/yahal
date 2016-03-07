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

#include "clk.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>
#include "../power_manager/power_manager.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::Clk::Clk(void)
{}



bool yahal::mcu::targets::msp430f5309::Clk::setFrequencyHz(uint32_t desiredFrequencyHz)
{
	//TODO: User user selected frequency

	yahal::mcu::targets::msp430f5309::PowerManager::getInstance().setVCoreLevel(3); // Increase core voltage to allow higher frequencies
	UCSCTL1 |= DCORSEL1 + DCORSEL2; //6
	UCSCTL2 = FLLD__16 + 0x1F;	// Approx 16Mhz
	UCSCTL3 = SELREF__REFOCLK;
	UCSCTL4 = SELM__DCOCLK + SELS__DCOCLK + SELA__REFOCLK;

	return true;
}



uint32_t yahal::mcu::targets::msp430f5309::Clk::getFrequencyHz(void)
{
	return 0;
}



/* ---------------------------------------------------------------------------------------------- */
#endif 	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
