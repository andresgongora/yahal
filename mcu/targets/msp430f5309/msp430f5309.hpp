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

#include "../../config/targets/msp430f5309/config.hpp"

#include "clk/clk.hpp"
#include "wdt/wdt.hpp"
#include "gpio/gpio.hpp"
#include "usci_b1/i2c/i2c_master.hpp"
#include "usci_b1/i2c/i2c_slave.hpp"
#include "usci_b1/i2c/i2c_multimaster.hpp"
#include "adc_10/adc_10.hpp"
#include "timer_a1/timer_a1.hpp"
#include "irq/irq_handler.hpp"
#include "power_manager/power_manager.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{

// WDT
#if YAHAL_MCU_MSP430F5309_WDT_ENABLED == true
	extern yahal::mcu::targets::msp430f5309::Wdt& wdt;
#endif


// CLK
#if YAHAL_MCU_MSP430F5309_CLK_ENABLED == true
	extern yahal::mcu::targets::msp430f5309::Clk& clk;
#endif


// GPIO
#if YAHAL_MCU_MSP430F5309_GPIO_ENABLED == true
	extern yahal::mcu::targets::msp430f5309::Gpio& gpio;
#endif


// USCI_B1
#if YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true
	#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
		extern yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
		extern yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
		extern yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster& YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI
		extern yahal::mcu::targets::msp430f5309::UsciB1::Spi YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
	#else
		#error "USCI_B1_MODE is not valid"
	#endif
#endif


// TIMER_A0
#if YAHAL_MCU_MSP430F5309_TIMER_A0_ENABLED == true
	extern yahal::mcu::targets::msp430f5309::TimerA0& timer_a0;
#endif


// TIMER_A1
#if YAHAL_MCU_MSP430F5309_TIMER_A1_ENABLED == true
	extern yahal::mcu::targets::msp430f5309::TimerA1& timer_a1;
#endif


// ADC_10
#if YAHAL_MCU_MSP430F5309_ADC_10_ENABLED == true
	extern yahal::mcu::targets::msp430f5309::Adc10& adc_10;
#endif


// IRQ
#if YAHAL_MCU_MSP430F5309_IRQ_ENABLED == true
	extern yahal::mcu::targets::msp430f5309::IrqHandler& irq;
#endif


namespace targets {
	bool init(void);
}



}} // yahal::mcu




/* ---------------------------------------------------------------------------------------------- */
#if false ////
/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	class Target;
}}


/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::Target
{
protected:
	Target(void);


	/// Initialize all modules.
	bool init(void);


public:
	// WDT
	#if YAHAL_MCU_MSP430F5309_WDT_ENABLED == true
		yahal::mcu::targets::msp430f5309::Wdt& wdt;
	#endif


	// CLK
	#if YAHAL_MCU_MSP430F5309_CLK_ENABLED == true
		yahal::mcu::targets::msp430f5309::Clk& clk;
	#endif


	// GPIO
	#if YAHAL_MCU_MSP430F5309_GPIO_ENABLED == true
		yahal::mcu::targets::msp430f5309::Gpio& gpio;
	#endif


	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true
		#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
			yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
			yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
			yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster& YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI
			yahal::mcu::targets::msp430f5309::UsciB1::Spi YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#else
			#error "USCI_B1_MODE is not valid"
		#endif
	#endif


	// TIMER_A0
	#if YAHAL_MCU_MSP430F5309_TIMER_A0_ENABLED == true
	//	yahal::mcu::targets::msp430f5309::TimerA0 timer_a0;
	#endif


	// IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_ENABLED == true
		yahal::mcu::targets::msp430f5309::IrqHandler& irq;
	#endif
};
#endif


/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif	// __YAHAL_MCU_MSP430F5309_HPP_INCLUDED__
