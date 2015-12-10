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


#ifndef __MSP430F2132_IRQ_HPP_INCLUDED__
#define __MSP430F2132_IRQ_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../msp430f5309.hpp"
#include "hal/utility/publish_subscribe.hpp"




/** --- DEFINE --------------------------------------------------------------------------------- **/



/* ============================================================================================== */
 *	hal::uc::msp430f2132::Irq
 * ============================================================================================== */
class hal::uc::msp430f2132::Irq : public hal::uc::Irq
{
public:
				// CONFIGURATION
	void			enableGlobalInterrupts(void) const;
	void			disableGlobalInterrupts(void) const;



	// PUBLISHERS
	utility::Publisher<hal::uc::Irq::Code::I2C::Type>	i2c;
	utility::Publisher<hal::uc::Irq::Code::UART::Type>	uart;
	utility::Publisher<hal::uc::Irq::Code::GPIO::Type>	gpio;
};



/* ============================================================================================== */
 *	hal::uc::msp430f2132::Irq :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	extern hal::uc::msp430f2132::Irq irq;
}}}


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__MSP430F2132_IRQ_HPP_INCLUDED__
