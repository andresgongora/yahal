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

#ifndef __YAHAL_MCU_MSP430F5309_USCIB1_I2CSLAVE_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_USCIB1_I2CSLAVE_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <stdint.h>
#include <cstddef>
#include "../../../../modules/i2c/i2c_slave.hpp"
#include "../usci_b1.hpp"




/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave :
	public yahal::mcu::modules::I2CSlave,
	public yahal::mcu::targets::msp430f5309::UsciB1
{
public:
				struct Configuration
				{
					uint8_t ownAddress;
				};


				// CONSTRUCTOR
				I2CSlave(const Configuration& configuration);


private:			// INITIALIZATION
	virtual void		initHW(void);


			// I2C PROTOCOL
	virtual void		writeBufferTX(uint8_t byte);
	virtual uint8_t		readBufferRX(void);
	virtual bool		isIncommingWrite(void);


				// ISR
	virtual void 		isr(UsciB1::Irq::Type irq);


				// PRIVATE VARIABLES
	const Configuration&	configuration_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif	// __YAHAL_MCU_MSP430F5309_USCIB1_I2CSLAVE_HPP_INCLUDED__
