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




#ifndef __YAHAL_MCU_MSP430F5309_CONFIG_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_CONFIG_HPP_INCLUDED__


#if MCU_DEVICE == MCU_MSP430F5309



/* ============================================================================================== */


//	+---------------------------------------------------------------+
#define	__YAHAL_MCU_MSP430F5309_CLK_ENABLED__	// Comment to disable
//	+---------------------------------------------------------------+

#ifdef	__YAHAL_MCU_MSP430F5309_CLK_ENABLED__
#define __YAHAL_MCU_MSP430F5309_CLK_INSTANCE_NAME__		clk
#define __YAHAL_MCU_MSP430F5309_CLK_FREQUENCY__			1000000
#define __YAHAL_MCU_MSP430F5309_CLK_FREQUENCY2__			20000
#endif




#define __YAHAL_MCU_MSP430F5309_WDT_ENABLED__	// Comment to disable





#define __YAHAL_MCU_MSP430F5309_GPIO_ENABLED__	// Comment to disable






//#define __YAHAL_MCU_MSP430F5309_I2C_MASTER_ENABLED__
//#define __YAHAL_MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__
//#define __YAHAL_MCU_MSP430F5309_I2C_SLAVE_ENABLED__




//#define __YAHAL_MCU_MSP430F5309_TIMER_ENABLED__



/*
#ifdef	__MSP430F5309_CLK_ENABLED__
	hal::uc::msp430f5309::clk	__MSP430F5309_CLK_INSTANCE_NAME__(
						__MSP430F5309_CLK_FREQUENCY__,
						__MSP430F5309_CLK_FREQUENCY2__
					);
#endif
*/



/* ---------------------------------------------------------------------------------------------- */
#endif // MCU_DEVICE == MCU_MSP430F5309
#endif //__YAHAL_MCU_MSP430F5309_CONFIGHPP_INCLUDED__
