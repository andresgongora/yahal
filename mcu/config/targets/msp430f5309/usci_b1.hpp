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

#ifndef __YAHAL_MCU_CONFIG_TARGETS_MSP430F5309_USCI_B1_HPP_INCLUDED__
#define __YAHAL_MCU_CONFIG_TARGETS_MSP430F5309_USCI_B1_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "config.hpp"
#if YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true

#include "../../../targets/msp430f5309/usci_b1/i2c/i2c_slave.hpp"
#include "../../../targets/msp430f5309/usci_b1/i2c/i2c_master.hpp"
#include "../../../targets/msp430f5309/usci_b1/i2c/i2c_multimaster.hpp"



namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{ namespace config{
/* ---------------------------------------------------------------------------------------------- */


// Slave
#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
	const yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::Configuration usci_b1 = {
	/* Own Address		*/ 0x1E,
	};


// Master
#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
	const yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::Configuration usci_b1 = {
	/* baud_rate_prescale	*/ 32,
	};


// Multimaster
#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
	const yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::Configuration usci_b1 = {
	/* Own Address		*/ 0x1E,
	/* baud_rate_prescale	*/ 32,
	};


// SPI
#elif  YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI


#else
	#error "USCI_B1_MODE is not valid"
#endif



/* ---------------------------------------------------------------------------------------------- */
}}}}}	// namespace yahal::mcu::targets::msp430f5309::config
#endif // YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true
#endif // __YAHAL_MCU_CONFIG_TARGETS_MSP430F5309_USCI_B1_HPP_INCLUDED__