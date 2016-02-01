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




#ifndef __YAHAL_MCU_MSP430F5309_USCI_B1_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_USCI_B1_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../config/targets/msp430f5309/config.hpp"
#if YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true






/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class UsciB1;
	class IrqHandler;	// Forward declaration
}}}}



/***********************************************************************************************//**
 * @brief	Base class for the USCI_B1 HW Module, used for I2C and SPI.
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::UsciB1
{
public:
	#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
		class I2CSlave;
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
		class I2CMaster;
	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
		class I2CMultimaster;
	#elif  YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI
		class Spi;
	#else
		#error "USCI_B1_MODE is not valid"
	#endif

protected:
				struct Irq { enum Type {
					I2C_START,
					I2C_STOP,
					I2C_TX_BUFFER_EMPTY,
					I2C_RX_BUFFER_FULL,
					I2C_ARBITRATION_LOST,
					I2C_NACK,
				};};

				// -----------------------------------------------------------------
protected:
				/// This is a base class
				UsciB1(void) {}


	friend class		IrqHandler;
	virtual void		isr(Irq::Type irq) = 0;
};



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif	// __YAHAL_MCU_MSP430F5309_USCI_B1_HPP_INCLUDED__

