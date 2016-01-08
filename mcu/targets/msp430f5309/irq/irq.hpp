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


#ifndef __MSP430F2132_IRQ_HPP_INCLUDED__
#define __MSP430F2132_IRQ_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../msp430f5309.hpp"
#include "hal/utility/publish_subscribe.hpp"




/** --- DEFINE --------------------------------------------------------------------------------- **/



/* ============================================================================================== */
 *	yahal::mcu::modules::msp430f2132::Irq
 * ============================================================================================== */
class yahal::mcu::modules::msp430f2132::Irq : public yahal::mcu::modules::Irq
{
public:
				// CONFIGURATION
	void			enableGlobalInterrupts(void) const;
	void			disableGlobalInterrupts(void) const;



	// PUBLISHERS
	utility::Publisher<yahal::mcu::modules::Irq::Code::I2C::Type>	i2c;
	utility::Publisher<yahal::mcu::modules::Irq::Code::UART::Type>	uart;
	utility::Publisher<yahal::mcu::modules::Irq::Code::GPIO::Type>	gpio;
};



/* ============================================================================================== */
 *	yahal::mcu::modules::msp430f2132::Irq :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	extern yahal::mcu::targets::msp430f2132::Irq irq;
}}}


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__MSP430F2132_IRQ_HPP_INCLUDED__
