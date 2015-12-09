// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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




/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <mcu/targets/msp430f2132/clk/clk.hpp>
#include <msp430f2132.h>

#ifdef __MSP430F2132_CLK_ENABLED__



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DEFINITION::CLK
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ============================================================================= INITIALIZATION **/

hal::uc::msp430f2132::Clk::Clk() :
	_frequencyHz(Frequency::DCO_8MHz)
{}



bool hal::uc::msp430f2132::Clk::init(void)
{
	bool success;
	if(setFrequencyHz(_frequencyHz))	// Set default frequency
	{
		this->setInitialized();
		success = true;
	}
	else
	{
		success = false;
	}
	return success;
}

/** ============================================================================== CONFIGURATION **/

bool hal::uc::msp430f2132::Clk::setFrequencyHz(uint32_t desiredFrequencyHz)
{
	bool success = true;
	this->clearErrorCode();


	switch(desiredFrequencyHz)
	{
	case Frequency::DCO_1MHz:
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
		this->setErrorCode(ERROR::FREQUENCY_NOT_AVAILABLE);
		break;
	}


	// TODO: FINISH THIS!!!!!
	BCSCTL2	=  0x00;			// MCLK = DCO = SMCLK
	BCSCTL3	|= LFXT1S_2;			// LFXT1 = VLO
	IFG1 	&= ~OFIFG;			// Clear OSCFault flag

	return success;
}



uint32_t hal::uc::msp430f2132::Clk::getFrequencyHz(void)
{
	return _frequencyHz;
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Clk :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace hal{namespace uc{namespace msp430f2132{
	hal::uc::msp430f2132::Clk clk;
}}}

/** ============================================================================================ **/
#endif // __MSP430F2132_CLK_ENABLED__
