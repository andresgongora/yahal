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




/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::Clk::Clk(const Configuration& configuration) :
	configuration_(configuration)
{}



void yahal::mcu::targets::msp430f5309::Clk::doInit(void)
{
	if(setFrequencyHz(configuration_.frequency))	// Set default frequency
	{
	}
	else
	{
		//TODO: set error code
	}
}

/* ---------------------------------------------------------------------------------------------- */

void SetVCoreUp (unsigned int level)
{
	// Open PMM registers for write access
	PMMCTL0_H = 0xA5;
	// Make sure no flags are set for iterative sequences
//	while ((PMMIFG & SVSMHDLYIFG) == 0);
//	while ((PMMIFG & SVSMLDLYIFG) == 0);
	// Set SVS/SVM high side new level
	SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
	// Set SVM low side to new level
	SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
	// Wait till SVM is settled
	while ((PMMIFG & SVSMLDLYIFG) == 0);
	// Clear already set flags
	PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
	// Set VCore to new level
	PMMCTL0_L = PMMCOREV0 * level;
	// Wait till new level reached
	if ((PMMIFG & SVMLIFG))
	while ((PMMIFG & SVMLVLRIFG) == 0);
	// Set SVS/SVM low side to new level
	SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
	// Lock PMM registers for write access
	PMMCTL0_H = 0x00;
}


bool yahal::mcu::targets::msp430f5309::Clk::setFrequencyHz(uint32_t desiredFrequencyHz)
{
	bool success = true;
	this->clearErrorCode();

/*
	switch(desiredFrequencyHz)
	{
	case Frequency::DCO_1MHz:
		UCSCTL0 =
		DCOCTL	=  CALDCO_1MHZ;			// Set DCO step + modulation
		BCSCTL1	=  CALBC1_1MHZ; 		// Set range
		_frequencyHz = Frequency::DCO_1MHz;	// Store
		break;

	case Frequency::DCO_8MHz:
		DCOCTL	=  CALDCO_8MHZ;  		// Set DCO step + modulation
		BCSCTL1	=  CALBC1_8MHZ; 		// Set range
		_frequencyHz = Frequency::DCO_8MHz;	// Store
		break;

	case Frequency::DCO_16MHz:
		DCOCTL	=  CALDCO_16MHZ;  		// Set DCO step + modulation
		BCSCTL1	=  CALBC1_16MHZ; 		// Set range
		_frequencyHz = Frequency::DCO_16MHz;	// Store
		break;

	default:
		success = false;
		this->setErrorCode(Error::FREQUENCY_NOT_AVAILABLE);
		break;
	}


	// TODO: FINISH THIS!!!!!
	BCSCTL2	=  0x00;			// MCLK = DCO = SMCLK
	_freqMHzPeripherals = getFreqMHzCPU();
	BCSCTL3	|= LFXT1S_2;			// LFXT1 = VLO
	IFG1 	&= ~OFIFG;			// Clear OSCFault flag
*/
	SetVCoreUp(3); // Increase core voltage to allow higher frequencies
	UCSCTL1 |= DCORSEL1 + DCORSEL2; //6
	UCSCTL2 = FLLD__16 + 0x1F;	// Approx 16Mhz
	UCSCTL3 = SELREF__REFOCLK;
	UCSCTL4 = SELM__DCOCLK + SELS__DCOCLK + SELA__REFOCLK;


	//INFO!!!!!
	//TODO!!!!
	//http://e2e.ti.com/support/microcontrollers/msp430/f/166/p/227228/799351


	return success;
}



uint32_t yahal::mcu::targets::msp430f5309::Clk::getFrequencyHz(void)
{
	return 0;
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
