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

#include "msp430f5309.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309





/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::Target::Target(void) :




	// CLK
	#if YAHAL_MCU_MSP430F5309_ENABLE_CLK == true
		clk(yahal::mcu::targets::msp430f5309::Clk::getInstance()),
	#endif


	// GPIO
	#if YAHAL_MCU_MSP430F5309_ENABLE_GPIO == true
		gpio(yahal::mcu::targets::msp430f5309::Gpio::getInstance()),
	#endif

	// ADC_10
	#if YAHAL_MCU_MSP430F5309_ENABLE_ADC_10 == true
		adc_10(yahal::mcu::targets::msp430f5309::Adc10::getInstance()),
	#endif

	// WDT
	#if YAHAL_MCU_MSP430F5309_ENABLE_WDT == true
		wdt(yahal::mcu::targets::msp430f5309::Wdt::getInstance())
	#endif

/*
	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true
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



	// TIMER A0
	#if YAHAL_MCU_MSP430F5309_TIMER_A0_ENABLED == true
		yahal::mcu::targets::msp430f5309::TimerA0 timer_a0(targets::msp430f5309::config::timer_a0);
	#endif


	//IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_ENABLED == true
		irq(yahal::mcu::targets::msp430f5309::IrqHandler::getInstance())
	#endif*/


{}// Constructor



/* ---------------------------------------------------------------------------------------------- */
bool yahal::mcu::Target::init(void)
{

	bool success = true;

/*	// WDT
	#if YAHAL_MCU_MSP430F5309_ENABLE_WDT == true
		success &= wdt.init();
	#endif


	// CLK
	#if YAHAL_MCU_MSP430F5309_ENABLE_CLK == true
		success &= clk.init();
	#endif


	// GPIO
	#if YAHAL_MCU_MSP430F5309_ENABLE_GPIO == true
		success &= gpio.init();
	#endif


	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true
		success &= YAHAL_MCU_MSP430F5309_USCI_B1_NAME.init();
	#endif


	// TIMER A0
	#if YAHAL_MCU_MSP430F5309_TIMER_A0_ENABLED == true
//		success &= timer_a0.init();
	#endif


	// IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_ENABLED == true
		irq.enableGlobalInterrupts();
	#endif
*/
	return success;
}// init



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
