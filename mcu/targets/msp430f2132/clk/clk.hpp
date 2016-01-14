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




#ifndef __MSP430F2132_CLK_HPP_INCLUDED__
#define __MSP430F2132_CLK_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"
#ifdef __MSP430F2132_CLK_ENABLED__

#include "hal/mcu/virtual/clk/clk.hpp"



/* ============================================================================================== */
 *	DECLARATION::CLK
 * ============================================================================================== */
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



/* ============================================================================================== */
 *	hal::uc::msp430f2132::Clk :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	extern hal::uc::msp430f2132::Clk clk;
}}}


/* ---------------------------------------------------------------------------------------------- */
#endif // __MSP430F2132_CLK_ENABLED__
#endif // __MSP430F2132_CLK_HPP_INCLUDED__
