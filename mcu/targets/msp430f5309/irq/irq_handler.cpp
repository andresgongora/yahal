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

/* ---------------------------------------------------------------------------------------------- */

#include <targets/msp430f5309/irq/irq_handler.hpp>
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::IRQHandler::IRQHandler(void) :
	p_handler_uscib1_(NULL)
{}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::IRQHandler::enableGlobalInterrupts(void) const
{
	_EINT();
}


void yahal::mcu::targets::msp430f5309::IRQHandler::disableGlobalInterrupts(void) const
{
	_DINT();
}



/* ---------------------------------------------------------------------------------------------- */


void yahal::mcu::targets::msp430f5309::IRQHandler::setISRHandlerUsciB1(UsciB1* p_handler)
{
	p_handler_uscib1_ = p_handler;
}



void yahal::mcu::targets::msp430f5309::IRQHandler::irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::IRQ::Type irq)
{
	if (p_handler_uscib1_) {
		p_handler_uscib1_->isr(irq);
	}
}

/* ---------------------------------------------------------------------------------------------- */






/* ---------------------------------------------------------------------------------------------- */
#endif // MCU_DEVICE == MCU_MSP430F5309
