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
#if MCU_DEVICE == MCU_MSP430F5309



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{ namespace config{




/* =================================================================================================
	CLK
================================================================================================= */

#define	__YAHAL_MCU_MSP430F5309_CLK_ENABLED__	true		///< Create instance

static const yahal::mcu::targets::msp430f5309::Clk::Configuration clk = {
/* Frequency	*/ msp430f5309::Clk::Frequency::DCO_8MHz,
/* Clock Source */ msp430f5309::Clk::ClockSource::VLP,
};



/* =================================================================================================
	GPIO
================================================================================================= */

#define	__YAHAL_MCU_MSP430F5309_GPIO_ENABLED__	true		///< Create instance

// CONFIGURATION
static const yahal::mcu::targets::msp430f5309::Gpio::Configuration gpio = {
/* Nothing	*/
};



/* =================================================================================================
	WDT
================================================================================================= */

#define	__YAHAL_MCU_MSP430F5309_WDT_ENABLED__	true		///< Create instance

// CONFIGURATION
static const yahal::mcu::targets::msp430f5309::Wdt::Configuration wdt = {
/* Nothing	*/
};





/* =================================================================================================
	I2C
================================================================================================= */


}}}}}	// namespace yahal::mcu::targets::msp430f5309::config











/* ============================================================================================== */




/* ---------------------------------------------------------------------------------------------- */
#endif // MCU_DEVICE == MCU_MSP430F5309
#endif //__YAHAL_MCU_TARGETS_MSP430F5309_CONFIGHPP_INCLUDED__
