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




#ifndef __YAHAL_MCU_TARGETS_MSP430F5309_CONFIG_HPP_INCLUDED__
#define __YAHAL_MCU_TARGETS_MSP430F5309_CONFIG_HPP_INCLUDED__

#include "../../targets/msp430f5309/msp430f5309.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{ namespace config{


/* =================================================================================================
	CLK
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_CLK_ENABLED		true

static const yahal::mcu::targets::msp430f5309::Clk::Configuration clk = {
/* Frequency	*/ msp430f5309::Clk::Frequency::DCO_8MHz,
/* Clock Source */ msp430f5309::Clk::ClockSource::VLP,
};





/* =================================================================================================
	GPIO
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_GPIO_ENABLED		true

static const yahal::mcu::targets::msp430f5309::Gpio::Configuration gpio = {
/* Nothing	*/
};





/* =================================================================================================
	WDT
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_WDT_ENABLED		true

static const yahal::mcu::targets::msp430f5309::Wdt::Configuration wdt = {
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
	USCIB1
================================================================================================= */

// AVAILABLE MODES
#define YAHAL_MCU_MSP430F5309_USCIB1_I2C_SLAVE		0
#define YAHAL_MCU_MSP430F5309_USCIB1_I2C_MASTER		1
#define YAHAL_MCU_MSP430F5309_USCIB1_I2C_MULTIMASTER	2
//#define YAHAL_MCU_MSP430F5309_USCIB1_SPI 		3	// Not implemented yet

/* ---------------------------------------------------------------------------------------------- */

#define	YAHAL_MCU_MSP430F5309_USCIB1_ENABLED		true
#define YAHAL_MCU_MSP430F5309_USCIB1_MODE		YAHAL_MCU_MSP430F5309_USCIB1_I2C_MULTIMASTER
#define YAHAL_MCU_MSP430F5309_USCIB1_NAME		i2c1


	// Slave
#if	YAHAL_MCU_MSP430F5309_USCIB1_ENABLED == true	\
&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_SLAVE
	static const yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::Configuration uscib1 = {
	/* Own Address	*/ 0x1E,
	};

	// Master
#elif	YAHAL_MCU_MSP430F5309_USCIB1_ENABLED == true	\
&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MASTER
	static const yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::Configuration uscib1 = {
	/* Nothing	*/
	};

	// Multimaster
#elif	YAHAL_MCU_MSP430F5309_USCIB1_ENABLED == true	\
&&	YAHAL_MCU_MSP430F5309_USCIB1_MODE == YAHAL_MCU_MSP430F5309_USCIB1_I2C_MULTIMASTER
	static const yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::Configuration uscib1 = {
	/* Own Address */ 0x1E,
	};
#endif



/* =================================================================================================
	X X X
================================================================================================= */






}}}}}	// namespace yahal::mcu::targets::msp430f5309::config











/* ============================================================================================== */




/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_TARGETS_MSP430F5309_CONFIGHPP_INCLUDED__
