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

#include "irq_handler.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>
#include "../usci_b1/usci_b1.hpp"
#include "../usci_b1/i2c/i2c_slave.hpp"
#include "../usci_b1/i2c/i2c_master.hpp"
#include "../usci_b1/i2c/i2c_multimaster.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::IrqHandler
yahal::mcu::targets::msp430f5309::IrqHandler::instance_;

yahal::mcu::targets::msp430f5309::IrqHandler&
yahal::mcu::targets::msp430f5309::IrqHandler::getInstance(void)
{
	return instance_;
}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::IrqHandler::enableGlobalInterrupts(void)
{
	_EINT();
}


void yahal::mcu::targets::msp430f5309::IrqHandler::disableGlobalInterrupts(void)
{
	_DINT();
}



/* =================================================================================================
	USCI_B1
================================================================================================= */
#if YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true
	#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE




	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER



	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER

		yahal::mcu::targets::msp430f5309::UsciB1&
		yahal::mcu::targets::msp430f5309::IrqHandler::handler_usci_b1_ =
			yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::getInstance();


		#pragma vector = USCI_B1_VECTOR
		__interrupt void yahal::mcu::targets::msp430f5309::IrqHandler::USCI_B1_ISR(void)
		{
			switch (__even_in_range(UCB1IV, 12))
			{
			case  0: ///< Vector 00: No interrupts
				break;
			case  2: ///< Vector 02: Arbitration Lost
				handler_usci_b1_.isr(UsciB1::Irq::I2C_ARBITRATION_LOST);
				break;
			case  4: ///< Vector 04: Nack
				handler_usci_b1_.isr(UsciB1::Irq::I2C_NACK);
				break;
			case  6: ///< Vector 06: Start
				handler_usci_b1_.isr(UsciB1::Irq::I2C_START);
				break;
			case  8: ///< Vector 08: Stop
				handler_usci_b1_.isr(UsciB1::Irq::I2C_STOP);
				break;
			case 10: ///< Vector 10: RX Full
				handler_usci_b1_.isr(UsciB1::Irq::I2C_RX_BUFFER_FULL);
				break;
			case 12: ///< Vector 12: TX Empty
				handler_usci_b1_.isr(UsciB1::Irq::I2C_TX_BUFFER_EMPTY);
				break;
			default:
				break;
			}
		}

	#else
		#error "USCI_B1_MODE is not valid"
	#endif
#endif



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
