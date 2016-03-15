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
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_CLK

#include <msp430f5309.h>



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::Clk::Clk(void)
{}



bool yahal::mcu::targets::msp430f5309::Clk::setFrequencyHz(uint32_t desiredFrequencyHz)
{
	//TODO: User user selected frequency

	setVCoreLevel(3); // Increase core voltage to allow higher frequencies
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



void yahal::mcu::targets::msp430f5309::Clk::setVCoreLevel(uint8_t level)
{
	uint8_t current_level = PMMCTL0_L & 0x03;
	if (current_level +1 < level) {					///< If difference greater than 1
		setVCoreLevel(level -1);				///< Increase iteratively
	} else if (current_level > level ) {
		return; ///<TODO: Decreasin Vcore is different from increasing in. Not implemented jet
	}


	PMMCTL0_H = 0xA5;						///< Open PMM registers for write access

	SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;///< Set SVS/SVM high side new level
	SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;			///< Set SVM low side to new level

	while ((PMMIFG & SVSMLDLYIFG) == 0);				///< Wait till SVM is settled

	PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);				///< Clear already set flags
	PMMCTL0_L = PMMCOREV0 * level;					///< Set VCore to new level

	if ((PMMIFG & SVMLIFG)) {
		while ((PMMIFG & SVMLVLRIFG) == 0);			///< Wait till new level reached
	}

	SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;///< Set SVS/SVM low side to new level

	PMMCTL0_H = 0x00;						///< Lock PMM registers for write access
}



/* ---------------------------------------------------------------------------------------------- */
#endif 	// YAHAL_MCU_MSP430F5309_ENABLE_CLK
