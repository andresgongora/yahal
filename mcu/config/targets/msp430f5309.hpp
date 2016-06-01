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


#include "../config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309



/* =================================================================================================
	GPIO
================================================================================================= */

#define	YAHAL_MCU_MSP430F5309_ENABLE_PORT1
//#define	YAHAL_MCU_MSP430F5309_ENABLE_PORT2
//#define	YAHAL_MCU_MSP430F5309_ENABLE_PORT3
//#define	YAHAL_MCU_MSP430F5309_ENABLE_PORT4
//#define	YAHAL_MCU_MSP430F5309_ENABLE_PORT5
//#define	YAHAL_MCU_MSP430F5309_ENABLE_PORT6

#define	YAHAL_MCU_MSP430F5309_NAME_PORT1	port1
#define	YAHAL_MCU_MSP430F5309_NAME_PORT2	port2
#define	YAHAL_MCU_MSP430F5309_NAME_PORT3	port3
#define	YAHAL_MCU_MSP430F5309_NAME_PORT4	port3
#define	YAHAL_MCU_MSP430F5309_NAME_PORT5	port4
#define	YAHAL_MCU_MSP430F5309_NAME_PORT6	port5


/* =================================================================================================
	WDT
================================================================================================= */
#define	YAHAL_MCU_MSP430F5309_ENABLE_WDT
#define	YAHAL_MCU_MSP430F5309_NAME_WDT		wdt


/* =================================================================================================
	CLK
================================================================================================= */
#define	YAHAL_MCU_MSP430F5309_ENABLE_CLK
#define	YAHAL_MCU_MSP430F5309_NAME_CLK		clk


/* ---------------------------------------------------------------------------------------------- */
//#define	YAHAL_MCU_MSP430F5309_ENABLE_IRQ
//#define	YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1

//#define	YAHAL_MCU_MSP430F5309_ENABLE_ADC_10



/* =================================================================================================
	USCI_B1
================================================================================================= */

// AVAILABLE MODES
#define YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE		0
#define YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER	1
#define YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER	2
//#define YAHAL_MCU_MSP430F5309_USCI_B1_SPI 		3	// Not implemented yet

/* ---------------------------------------------------------------------------------------------- */

//#define	YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED		true
#define YAHAL_MCU_MSP430F5309_USCI_B1_MODE		YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
#define YAHAL_MCU_MSP430F5309_USCI_B1_NAME		i2c1





/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif	// __YAHAL_MCU_TARGETS_MSP430F5309_CONFIGHPP_INCLUDED__
