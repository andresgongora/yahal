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
	*	|		ACLK is software selectable for individual peripheral modules	|
	*	|										|
	*	|	MCLK:	Master clock. MCLK is software selectable as			|
	*	|		MCLK is used by the CPU and system				|
	*	|										|
	*	|	SMCLK:	Sub-main clock. SMCLK is software selectable as			|
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

#ifndef __MCU_MSP430F5309_CLK_HPP_INCLUDED__
#define __MCU_MSP430F5309_CLK_HPP_INCLUDED__



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../msp430f5309_config.hpp"
#ifdef __MCU_MSP430F5309_CLK_ENABLED__

#include "../../../modules/clk/clk.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace targets{ namespace msp430f5309{
	class Clk;
}}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION::CLK
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/
class mcu::targets::msp430f5309::Clk : public mcu::Clk
{
public:
	struct Frequency{enum type{
		DCO_1MHz = 1000000,
		DCO_2MHz = 2000000,
		DCO_4MHz = 4000000,
		DCO_8MHz = 8000000,
		DCO_16MHz = 16000000,
		DCO_32MHz = 32000000
	};};

				// CONSTRUCTOR
				Clk(void);



private:			// INITIALIZATION
	void			doInit(void);



				// CONFIGURATION
	bool			setFrequencyHz(uint32_t desiredFrequencyHz);
	uint32_t		getFrequencyHz(void);



private:
				// CONFIGURATION
	uint32_t		_frequencyHz;
//	uint32_t		_freqMHzPeripherals;
};



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Clk :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace mcu{
	extern mcu::targets::msp430f5309::Clk clk;
}


/** ============================================================================================ **/
#endif // __MCU_MSP430F5309_CLK_ENABLED__
#endif // __MCU_MSP430F5309_CLK_HPP_INCLUDED__
