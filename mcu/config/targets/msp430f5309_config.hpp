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

#ifndef __YAHAL_MCU_TARGETS_MSP430F5309_CONFIG_HPP_INCLUDED__
#define __YAHAL_MCU_TARGETS_MSP430F5309_CONFIG_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../targets/msp430f5309/clk/clk.hpp"
#include "../../targets/msp430f5309/wdt/wdt.hpp"
#include "../../targets/msp430f5309/gpio/gpio.hpp"
#include "../../targets/msp430f5309/usci_b1/i2c/i2c_master.hpp"
#include "../../targets/msp430f5309/usci_b1/i2c/i2c_slave.hpp"
#include "../../targets/msp430f5309/usci_b1/i2c/i2c_multimaster.hpp"
#include "../../targets/msp430f5309/timer_a0/timer_a0.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{ namespace config{



/* =================================================================================================
	CLK
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE		true

const yahal::mcu::targets::msp430f5309::Clk::Configuration clk = {
/* Frequency	*/ msp430f5309::Clk::Frequency::DCO_8MHz,
/* Clock Source */ msp430f5309::Clk::ClockSource::VLP,
};



/* =================================================================================================
	GPIO
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_GPIO_INSTANTIATE		true

const yahal::mcu::targets::msp430f5309::Gpio::Configuration gpio = {
/* Nothing	*/
};



/* =================================================================================================
	WDT
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_WDT_INSTANTIATE		true

const yahal::mcu::targets::msp430f5309::Wdt::Configuration wdt = {
/* Nothing	*/
};



/* =================================================================================================
	USCIA0
================================================================================================= */

/* =================================================================================================
	USCIB0
================================================================================================= */

/* =================================================================================================
	USCIA1
================================================================================================= */

/* =================================================================================================
	USCI_B1
================================================================================================= */

// AVAILABLE MODES
#define YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE		0
#define YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER	1
#define YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER	2
//#define YAHAL_MCU_MSP430F5309_USCI_B1_SPI 		3	// Not implemented yet

/* ---------------------------------------------------------------------------------------------- */

#define	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE	true
#define YAHAL_MCU_MSP430F5309_USCI_B1_MODE		YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
#define YAHAL_MCU_MSP430F5309_USCI_B1_NAME		i2c1


	// Slave
#if	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
	const yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::Configuration usci_b1 = {
	/* Own Address		*/ 0x1E,
	};

	// Master
#elif	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
	const yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::Configuration usci_b1 = {
	/* baud_rate_prescale	*/ 32,
	};

	// Multimaster
#elif	YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true	\
&&	YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
	const yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::Configuration usci_b1 = {
	/* Own Address		*/ 0x1E,
	/* baud_rate_prescale	*/ 32,
	};
#endif



/* =================================================================================================
	TIMER_A0
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE	true

const yahal::mcu::targets::msp430f5309::TimerA0::Configuration timer_a0 = {
/* clock_source		*/ TimerA0::ClockSource::VLP,
/* ccr0_output_enable	*/ false,
/* ccr1_output_enable	*/ false,
/* ccr2_output_enable	*/ false,
/* ccr3_output_enable	*/ false,
/* ccr4_output_enable	*/ false,
};



/* =================================================================================================
	TIMER_A1
================================================================================================= */

/* =================================================================================================
	TIMER_B0
================================================================================================= */

/* =================================================================================================
	TIMER_B1
================================================================================================= */




/* =================================================================================================
	IRQ
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_IRQ_INSTANTIATE	true






/* ---------------------------------------------------------------------------------------------- */
}}}}}	// namespace yahal::mcu::targets::msp430f5309::config



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_TARGETS_MSP430F5309_CONFIGHPP_INCLUDED__
