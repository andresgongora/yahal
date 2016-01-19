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

#include "../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "msp430f5309.hpp"



/* =================================================================================================
	MODULES
================================================================================================= */
#include "../../config/targets/msp430f5309_config.hpp"

#include "clk/clk.hpp"
#include "wdt/wdt.hpp"
#include "gpio/gpio.hpp"
#include "uscib1/i2c/i2c_master.hpp"
#include "uscib1/i2c/i2c_slave.hpp"
#include "uscib1/i2c/i2c_multimaster.hpp"

#include "irq/irq_handler.hpp"




/* =================================================================================================
	INSTANCES
================================================================================================= */

namespace yahal{ namespace mcu{

	/* -------------------------------------------------------------------------------------- */

	// IrqHandler
	targets::msp430f5309::IrqHandler irq_handler;

	/* -------------------------------------------------------------------------------------- */

	// CLK
	#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
		targets::msp430f5309::Clk clk(targets::msp430f5309::config::clk);
	#endif

	/* -------------------------------------------------------------------------------------- */

	// GPIO
	#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
		targets::msp430f5309::Gpio gpio(targets::msp430f5309::config::gpio);
	#endif

	/* -------------------------------------------------------------------------------------- */

	// USCIB1
	#if	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_SLAVE
		targets::msp430f5309::UsciB1::I2CSlave	\
		YAHAL_MCU_MSP430F5309_USCIB1_NAME		\
		(targets::msp430f5309::config::uscib1);

	#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MASTER
		targets::msp430f5309::UsciB1::I2CMaster	\
		YAHAL_MCU_MSP430F5309_USCIB1_NAME		\
		(targets::msp430f5309::config::uscib1);

	#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MULTIMASTER
		targets::msp430f5309::UsciB1::I2CMultimaster	\
		YAHAL_MCU_MSP430F5309_USCIB1_NAME			\
		(targets::msp430f5309::config::uscib1);
	#endif

	/* -------------------------------------------------------------------------------------- */

	// WDT
	#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
		targets::msp430f5309::Wdt wdt(targets::msp430f5309::config::wdt);
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
//	irq_handler.setISRHandlerUsciB1(&yahal::mcu::YAHAL_MCU_MSP430F5309_USCIB1_NAME);
	#endif
	// ...
	irq_handler.enableGlobalInterrupts();
}



}}} // Namespace yahal::mcu::details




	// CLK
#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Clk
		yahal::mcu::targets::Target::clk
			(yahal::mcu::targets::msp430f5309::config::clk);
#endif

// GPIO
#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Gpio
		yahal::mcu::targets::Target::gpio
			(yahal::mcu::targets::msp430f5309::config::gpio);
#endif

// USCI_B1
#if	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_SLAVE
	yahal::mcu::targets::Target::YAHAL_MCU_MSP430F5309_USCIB1_NAME(yahal::mcu::targets::msp430f5309::config::uscib1),

#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MASTER
	yahal::mcu::targets::Target::YAHAL_MCU_MSP430F5309_USCIB1_NAME(yahal::mcu::targets::msp430f5309::config::uscib1),

#elif	YAHAL_MCU_MSP430F5309_USCIB1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MULTIMASTER
	yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster
		yahal::mcu::targets::Target::YAHAL_MCU_MSP430F5309_USCIB1_NAME
			(yahal::mcu::targets::msp430f5309::config::uscib1);
#endif

// WDT
#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Wdt
		yahal::mcu::targets::Target::wdt
			(yahal::mcu::targets::msp430f5309::config::wdt);
#endif

























/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
