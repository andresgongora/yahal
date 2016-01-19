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

/* ---------------------------------------------------------------------------------------------- */

#include "targets/msp430f5309/irq/irq_handler.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::IrqHandler::IrqHandler(void) //:
//	p_handler_uscib1_(NULL)
{}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::IrqHandler::enableGlobalInterrupts(void) const
{
	_EINT();
}


void yahal::mcu::targets::msp430f5309::IrqHandler::disableGlobalInterrupts(void) const
{
	_DINT();
}



/* ---------------------------------------------------------------------------------------------- */


void yahal::mcu::targets::msp430f5309::IrqHandler::setISRHandlerUsciB1(UsciB1* p_handler)
{
	p_handler_uscib1_ = p_handler;
}



void yahal::mcu::targets::msp430f5309::IrqHandler::irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::Type irq)
{
	if (p_handler_uscib1_) {
		p_handler_uscib1_->isr(irq);
	}
}

/* ---------------------------------------------------------------------------------------------- */


yahal::mcu::targets::msp430f5309::UsciB1* yahal::mcu::targets::msp430f5309::IrqHandler::p_handler_uscib1_=0;
#pragma vector = USCI_B1_VECTOR
__interrupt void yahal::mcu::targets::msp430f5309::IrqHandler::USCI_B1_ISR(void)
{
	switch (__even_in_range(UCB1IV, 12))
	{
	case 0: ///< Vector 00: No interrupts
		break;
	case 2: ///< Vector 02: Arbitration Lost
		irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_ARBITRATION_LOST);
		break;
	case 4: ///< Vector 04: Nack
		irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_NACK);
		break;
	case 6: ///< Vector 06: Start
		irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_START);
		break;
	case 8: ///< Vector 08: Stop
		irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_STOP);
		break;
	case 10: ///< Vector 10: RX Full
		irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_RX_BUFFER_FULL);
		break;
	case 12: ///< Vector 12: TX Empty
		irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_TX_BUFFER_EMPTY);
		break;
	default:
		break;
	}

}




/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
