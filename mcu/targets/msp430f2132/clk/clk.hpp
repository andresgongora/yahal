// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*    AUTOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|	SOURCES:________________________________________________________	|
	*	|	ACLK:	Auxiliary clock. ACLK is SW selectable as LFXT1CLK or VLOCLK.	|
	*	|		ACLK is divided by 1, 2, 4, or 8.				|
	*	|		ACLK is software selectable for individual peripheral modules	|
	*	|										|
	*	|	MCLK:	Master clock. MCLK is software selectable as			|
	*	|		LFXT1CLK, VLOCLK, XT2CLK (if available onchip), or DCOCLK.	|
	*	|		MCLK is divided by 1,2,4,or8. MCLK is used by the CPU and system|
	*	|										|
	*	|	SMCLK:	Sub-main clock. SMCLK is software selectable as			|
	*	|		LFXT1CLK, VLOCLK, XT2CLK (if available on-chip), or DCOCLK.	|
	*	|		SMCLK is divided by 1, 2, 4, or 8.				|
	*	|		SMCLK is software selectable for individual peripheral modules.	|
	*	|										|
	*	|										|
	*	|										|
	*	|	CLOCKS:_________________________________________________________	|
	*	|	LFXT1CLK:	Low-frequency/high-frequency oscillator			|
	*	|	DCOCLK: 	Internal digitally controlled oscillator (DCO).		|
	*	|	VLOCLK: 	Internal very low power, low frequency 12-kHz typical	|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/

#ifndef __MSP430F2132_CLK_HPP_INCLUDED__
#define __MSP430F2132_CLK_HPP_INCLUDED__



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"
#ifdef __MSP430F2132_CLK_ENABLED__

#include "hal/mcu/virtual/clk/clk.hpp"



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION::CLK
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/
class hal::uc::msp430f2132::Clk : public hal::uc::Clk
{
public:
	struct Frequency{enum type{
		DCO_1MHz = 1000000,
		DCO_8MHz = 8000000,
		DCO_16MHz = 16000000,
	};};

				// CONSTRUCTOR
				Clk(void);


				// INITIALIZATION
	bool			init(void);


				// CONFIGURATION
	bool			setFrequencyHz(uint32_t desiredFrequencyHz);
	uint32_t		getFrequencyHz(void);



private:
				// CONFIGURATION
	uint32_t		_frequencyHz;
//	uint32_t		_freqMHzPeripherals;
};



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Clk :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace hal{namespace uc{namespace msp430f2132{
	extern hal::uc::msp430f2132::Clk clk;
}}}


/** ============================================================================================ **/
#endif // __MSP430F2132_CLK_ENABLED__
#endif // __MSP430F2132_CLK_HPP_INCLUDED__
