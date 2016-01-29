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
#include "../../config/targets/msp430f5309/config.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{

// WDT
#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Wdt& wdt = yahal::mcu::targets::msp430f5309::Wdt::getInstance();
#endif


// CLK
#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Clk& clk = yahal::mcu::targets::msp430f5309::Clk::getInstance();
#endif


// GPIO
#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Gpio& gpio = yahal::mcu::targets::msp430f5309::Gpio::getInstance();
#endif


// USCI_B1
#if YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true
	#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
		yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
		yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
		yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster& YAHAL_MCU_MSP430F5309_USCI_B1_NAME = yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::getInstance();
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI
		yahal::mcu::targets::msp430f5309::UsciB1::Spi YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
	#else
		#error "USCI_B1_MODE is not valid"
	#endif
#endif


// TIMER A0
#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::TimerA0& timer_a0 = yahal::mcu::targets::msp430f5309::TimerA0::getInstance();
#endif


// TIMER_A1
#if YAHAL_MCU_MSP430F5309_TIMER_A1_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::TimerA1& timer_a1 = yahal::mcu::targets::msp430f5309::TimerA1::getInstance();
#endif


// ADC_10
#if YAHAL_MCU_MSP430F5309_ADC_10_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::Adc10& adc_10 = yahal::mcu::targets::msp430f5309::Adc10::getInstance();
#endif


//IRQ
#if YAHAL_MCU_MSP430F5309_IRQ_INSTANTIATE == true
	yahal::mcu::targets::msp430f5309::IrqHandler& irq = yahal::mcu::targets::msp430f5309::IrqHandler::getInstance();
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


	// TIMER_A0
	#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
		success &= timer_a0.init();
	#endif


	// TIMER_A1
	#if YAHAL_MCU_MSP430F5309_TIMER_A1_INSTANTIATE == true
		success &= timer_a1.init();
	#endif


	// ADC_10
	#if YAHAL_MCU_MSP430F5309_ADC_10_INSTANTIATE == true
		success &= adc_10.init();
	#endif


	// IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_INSTANTIATE == true
		irq.enableGlobalInterrupts();
	#endif

	return success;
}




#if false /////
/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::Target::Target(void) :
	// WDT
	#if YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE == true
		wdt(yahal::mcu::targets::msp430f5309::Wdt::getInstance()),
	#endif


	// CLK
	#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true
		clk(yahal::mcu::targets::msp430f5309::Clk::getInstance()),
	#endif


	// GPIO
	#if YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE == true
		gpio(yahal::mcu::targets::msp430f5309::Gpio::getInstance()),
	#endif


	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true
		#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
			yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
			yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
			YAHAL_MCU_MSP430F5309_USCI_B1_NAME(yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::getInstance()),
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI
			yahal::mcu::targets::msp430f5309::UsciB1::Spi YAHAL_MCU_MSP430F5309_USCI_B1_NAME(targets::msp430f5309::config::usci_b1);
		#else
			#error "USCI_B1_MODE is not valid"
		#endif
	#endif


	/*
	// TIMER A0
	#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
		yahal::mcu::targets::msp430f5309::TimerA0 timer_a0(targets::msp430f5309::config::timer_a0);
	#endif
	*/

	//IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_INSTANTIATE == true
		irq(yahal::mcu::targets::msp430f5309::IrqHandler::getInstance())
	#endif
{}// Constructor



/* ---------------------------------------------------------------------------------------------- */
bool yahal::mcu::Target::init(void)
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


	// TIMER A0
	#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
//		success &= timer_a0.init();
	#endif


	// IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_INSTANTIATE == true
		irq.enableGlobalInterrupts();
	#endif

	return success;
}// init
#endif


/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
