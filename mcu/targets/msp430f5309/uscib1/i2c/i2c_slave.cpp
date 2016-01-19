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






/* ---------------------------------------------------------------------------------------------- */
#include "i2c_slave.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>


/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::I2CSlave(const Configuration& configuration) :
	configuration_(configuration)
{}



void yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::initHW(void)
{
	UCB1CTL1 |= UCSWRST;				///< Enable SW reset

	P4SEL |= 0x06;					///< Config GPIO pins
	UCB1CTL1 = UCSSEL__SMCLK + UCSWRST;		///< SMCLK clock source (keep SW reset)
	UCB1CTL0 = UCMODE_3 + UCSYNC;			///< I2C mode + syncrhonous
	UCB1I2COA = configuration_.ownAddress;		///< Set own slave address
	UCB1CTL1 &= ~UCSWRST;				///< Clear SW Reset

	UCB1IE |= UCTXIE + UCRXIE + UCSTTIE + UCSTPIE;	///< Enable IE
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::writeBufferTX(uint8_t byte)
{
	UCB1TXBUF = byte;
}



uint8_t yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::readBufferRX(void)
{
	return UCB1RXBUF;
}



bool yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::isIncommingWrite(void)
{
	return (UCB1CTL1 & UCTR);
}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave::isr(UsciB1::Irq::Type irq)
{
	switch (irq)
	{
	case UsciB1::Irq::I2C_START:
		handleReceivedStart();
		break;
	case UsciB1::Irq::I2C_STOP:
		handleReceivedStop();
		break;
	case UsciB1::Irq::I2C_TX_BUFFER_EMPTY:
		handleBufferTXEmpty();
		break;
	case UsciB1::Irq::I2C_RX_BUFFER_FULL:
		handleBufferRXFull();
		break;
	default:
		break;
	}
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
