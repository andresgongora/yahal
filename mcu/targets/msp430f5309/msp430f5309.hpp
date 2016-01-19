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

#ifndef __YAHAL_MCU_MSP430F5309_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>



/* =================================================================================================
	MODULES
================================================================================================= */
#include "clk/clk.hpp"
#include "wdt/wdt.hpp"
#include "gpio/gpio.hpp"
#include "uscib1/i2c/i2c_master.hpp"
#include "uscib1/i2c/i2c_slave.hpp"
#include "uscib1/i2c/i2c_multimaster.hpp"

#include "irq/irq_handler.hpp"
//#include "hal/mcu/devices/msp430f5309/uart/uart.hpp"



// Include all modules before the configuration
#include "../../config/targets/msp430f5309_config.hpp"



/* =================================================================================================
	INSTANCES
================================================================================================= */

namespace yahal{ namespace mcu{

	/* -------------------------------------------------------------------------------------- */

	// IrqHandler
	static targets::msp430f5309::IrqHandler irq_handler;

	/* -------------------------------------------------------------------------------------- */

	// CLK
	#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
		static targets::msp430f5309::Clk clk(targets::msp430f5309::config::clk);
	#endif

	/* -------------------------------------------------------------------------------------- */

	// GPIO
	#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
		static targets::msp430f5309::Gpio gpio(targets::msp430f5309::config::gpio);
	#endif

	/* -------------------------------------------------------------------------------------- */

	// USCIB1
	#if	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_SLAVE
		static targets::msp430f5309::UsciB1::I2CSlave	\
		YAHAL_MCU_MSP430F5309_USCIB1_NAME		\
		(targets::msp430f5309::config::uscib1);

	#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MASTER
		static targets::msp430f5309::UsciB1::I2CMaster	\
		YAHAL_MCU_MSP430F5309_USCIB1_NAME		\
		(targets::msp430f5309::config::uscib1);

	#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MULTIMASTER
		static targets::msp430f5309::UsciB1::I2CMultimaster	\
		YAHAL_MCU_MSP430F5309_USCIB1_NAME			\
		(targets::msp430f5309::config::uscib1);
	#endif

	/* -------------------------------------------------------------------------------------- */

	// WDT
	#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
		static targets::msp430f5309::Wdt wdt(targets::msp430f5309::config::wdt);
	#endif

}} // Namespace yahal::mcu





/* =================================================================================================
	TARGET INITIALIZATION
================================================================================================= */

namespace yahal{ namespace mcu{ namespace details{

void initIrq(void);	// Forward declaration

/// Call all init functions for this targets modules.
void initTarget(void)
{
	// CLK
	#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
	yahal::mcu::clk.init();
	#endif

	// GPIO
	#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
	yahal::mcu::gpio.init();
	#endif

	// USCIB1
	#if YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true
	yahal::mcu::YAHAL_MCU_MSP430F5309_USCIB1_NAME.init();
	#endif

	// WDT
	#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
	yahal::mcu::wdt.init();
	#endif

	// IrqHandler
	initIrq();

}


/// Initialize everything Irq related
void initIrq(void)
{
	#if YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true
	irq_handler.setISRHandlerUsciB1(&yahal::mcu::YAHAL_MCU_MSP430F5309_USCIB1_NAME);
	#endif
	// ...
	irq_handler.enableGlobalInterrupts();
}



}}} // Namespace yahal::mcu::details





/***********************************************************************************************//**
 * @brief	USCIB1 Irq
 **************************************************************************************************/

/*#pragma vector = USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
	#if	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_SLAVE

	// -----------------------------------------------------------------------------------------


	#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MASTER

	// -----------------------------------------------------------------------------------------

	#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MULTIMASTER

		switch (__even_in_range(UCB1IV, 12))
		{
		case  0: ///< Vector 00: No interrupts
			break;
		case  2: ///< Vector 02: Arbitration Lost
			yahal::mcu::irq_handler.irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_ARBITRATION_LOST);
			break;
		case  4: ///< Vector 04: Nack
			yahal::mcu::irq_handler.irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_NACK);
			break;
		case  6: ///< Vector 06: Start
			yahal::mcu::irq_handler.irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_START);
			break;
		case  8: ///< Vector 08: Stop
			yahal::mcu::irq_handler.irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_STOP);
			break;
		case 10: ///< Vector 10: RX Full
			yahal::mcu::irq_handler.irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_RX_BUFFER_FULL);
			break;
		case 12: ///< Vector 12: TX Empty
			yahal::mcu::irq_handler.irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::Irq::I2C_TX_BUFFER_EMPTY);
			break;
		default:
			break;
		}
	#endif
}
*/

/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif	// __YAHAL_MCU_MSP430F5309_HPP_INCLUDED__
