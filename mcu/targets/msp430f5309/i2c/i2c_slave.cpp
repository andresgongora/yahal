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






/* ---------------------------------------------------------------------------------------------- */
#include "i2c_slave.hpp"
#if MCU_DEVICE == MCU_MSP430F5309

#include <msp430f5309.h>


/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::I2C_slave::I2C_slave(const Configuration& configuration) :
	_configuration(configuration)
{}



void yahal::mcu::targets::msp430f5309::I2C_slave::doInit(void)
{
	UCB1CTL1 |= UCSWRST;				///< Enable SW reset

	P4SEL |= 0x06;					///< Config GPIO pins
	UCB1CTL1 = UCSSEL__SMCLK + UCSWRST;		///< SMCLK clock source (keep SW reset)
	UCB1CTL0 = UCMODE_3 + UCSYNC;			///< I2C mode + syncrhonous
	UCB1I2COA = _configuration.ownAddress;		///< Set own slave address
	UCB1CTL1 &= ~UCSWRST;				///< Clear SW Reset

	UCB1IE |= UCTXIE + UCRXIE + UCSTTIE + UCSTPIE;	///< Enable IE
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::I2C_slave::writeBufferTX(uint8_t byte)
{
	UCB1TXBUF = byte;
}



uint8_t yahal::mcu::targets::msp430f5309::I2C_slave::readBufferRX(void)
{
	return UCB1RXBUF;
}



bool yahal::mcu::targets::msp430f5309::I2C_slave::isIncommingWrite(void)
{
	return (UCB1CTL1 & UCTR);
}



/* ---------------------------------------------------------------------------------------------- */
#endif // MCU_DEVICE == MCU_MSP430F5309
