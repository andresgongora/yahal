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
#include "../../config/targets/msp430f5309_config.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{

// WDT
#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
	targets::msp430f5309::Wdt wdt(targets::msp430f5309::config::wdt);
#endif


// CLK
#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
	targets::msp430f5309::Clk clk(targets::msp430f5309::config::clk);
#endif


// GPIO
#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
	targets::msp430f5309::Gpio gpio(targets::msp430f5309::config::gpio);
#endif


// USCI_B1
#if YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true
	#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
		targets::msp430f5309::UsciB1::I2CSlave YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
		targets::msp430f5309::UsciB1::I2CMaster YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
		targets::msp430f5309::UsciB1::I2CMultimaster YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI
		targets::msp430f5309::UsciB1::Spi YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
	#endif

	targets::msp430f5309::UsciB1& targets::msp430f5309::IrqHandler::handler_usci_b1_= YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
#endif


// GPIO
#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
	targets::msp430f5309::TimerA0 timer_a0(targets::msp430f5309::config::timer_a0);
#endif


// IRQ
#if YAHAL_MCU_MSP430F5309_IRQ_INSTANTIATE == true
	targets::msp430f5309::IrqHandler Irq;
#endif




}} // yahal::mcu
/* ---------------------------------------------------------------------------------------------- */





bool yahal::mcu::targets::init(void)
{

	bool success = true;

	// WDT
	#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
		success &= wdt.init();
	#endif


	// CLK
	#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
		success &= clk.init();
	#endif


	// GPIO
	#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
		success &= gpio.init();
	#endif


	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true
		success &= YAHAL_MCU_MSP430F5309_USCI_B1_NAME.init();
	#endif


	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
		success &= timer_a0.init();
	#endif


	// IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_INSTANTIATE == true
	Irq.enableGlobalInterrupts();
	#endif

	return success;
}




#if false
/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::Target::Target(void)
{}


/* ---------------------------------------------------------------------------------------------- */
void yahal::mcu::Target::init(void)
{
	// WDT
	#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
		wdt.init();
	#endif

	// CLK
	#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
		clk.init();
	#endif

	// GPIO
	#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
		gpio.init();
	#endif

	// USCI_B1
	#if	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
		YAHAL_MCU_MSP430F5309_USCI_B1_NAME.init();

	#elif	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
		YAHAL_MCU_MSP430F5309_USCI_B1_NAME.init();

	#elif	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
	&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
		YAHAL_MCU_MSP430F5309_USCI_B1_NAME.init();
	#endif
}



/* ---------------------------------------------------------------------------------------------- */

// WDT
#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Wdt
		yahal::mcu::Target::wdt
			(yahal::mcu::targets::msp430f5309::config::wdt);
#endif


// CLK
#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Clk
		yahal::mcu::Target::clk
			(yahal::mcu::targets::msp430f5309::config::clk);
#endif



// GPIO
#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Gpio
		yahal::mcu::Target::gpio
			(yahal::mcu::targets::msp430f5309::config::gpio);
#endif



// USCI_B1
#if	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
	yahal::mcu::Target::YAHAL_MCU_MSP430F5309_USCI_B1_NAME(yahal::mcu::targets::msp430f5309::config::usci_b1),

#elif	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
	yahal::mcu::Target::YAHAL_MCU_MSP430F5309_USCI_B1_NAME(yahal::mcu::targets::msp430f5309::config::usci_b1),

#elif	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
	yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster
		yahal::mcu::Target::YAHAL_MCU_MSP430F5309_USCI_B1_NAME
			(yahal::mcu::targets::msp430f5309::config::usci_b1);
#endif



#if	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true					\
&&(	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE		\
||	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER		\
||	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER	)
		yahal::mcu::targets::msp430f5309::UsciB1* const				\
		yahal::mcu::targets::msp430f5309::IrqHandler::p_handler_usci_b1_= 	\
		&yahal::mcu::Target::YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
#else
		yahal::mcu::targets::msp430f5309::UsciB1* const				\
		yahal::mcu::targets::msp430f5309::IrqHandler::p_handler_usci_b1_= 0;
#endif

#endif


























/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
