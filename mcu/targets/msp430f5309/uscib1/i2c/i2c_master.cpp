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
#include "i2c_master.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::I2CMaster(const Configuration& configuration) :
	configuration_(configuration)
{}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::doInit(void)
{
	UCB1CTL1 |= UCSWRST;				///< Enable SW reset while we configure the module
	P4SEL |= BIT1 + BIT2;				///< Assign I2C pins to USCI_B0

	UCB1CTL0 = UCMST | UCMODE_3 | UCSYNC;		///< I2C Master, synchronous mode
	UCB1CTL1 = UCSSEL__SMCLK | UCSWRST | UCTR;	///< Use SMCLK
	UCB1BRW = 12;					///< fSCL = SMCLK/12 = ~100kHz TODO: CALCULATE ASKING CLK!

	UCB1CTL1 &= ~UCSWRST;				///< Clear SW reset, resume operation

	UCB1IE |= UCRXIE + UCTXIE + UCNACKIE;		///< Enable RX interrupt
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::start(uint8_t slaveAddress, Direction::Type direction)
{
	while(UCB1STAT & UCBBUSY);			///< Recommended to check

	if (direction == Direction::WRITE) {
		UCB1CTL1 |= UCTR;			///< Set transmitter
	} else {
		UCB1CTL1 &= ~UCTR;			///< Set receiver
	}

	UCB1I2CSA = slaveAddress;			///< Bit shifting done by HW
	UCB1CTL1 |= UCTXSTT;				///< Send start
}



void yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::stop(void)
{
	while(UCB1CTL1 & UCTXSTT);	///< Wait if START in progress
	UCB1CTL1 |= UCTXSTP;
}



void yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::writeBufferTX(uint8_t byte)
{
	UCB1TXBUF = byte;
}



uint8_t yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::readBufferRX(void)
{
	return UCB1RXBUF;
}



void yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::awaitTransmissionEnd(void)
{
	while(UCB1STAT & UCBBUSY);
//	UCB1CTL1 &= ~(UCTR + UCTXNACK + UCTXSTP + UCTXSTT); // I think I dont need this anymore
}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster::isr(UsciB1::IRQ::Type irq)
{
	switch (irq)
	{
	case UsciB1::IRQ::I2C_TX_BUFFER_EMPTY:
		handleBufferTXEmpty();
		break;
	case UsciB1::IRQ::I2C_RX_BUFFER_FULL:
		handleBufferRXFull();
		break;
	case UsciB1::IRQ::I2C_NACK:
		handleReceivedNack();
		break;
	default:
		break;
	}
}

/* ---------------------------------------------------------------------------------------------- */
#endif // MCU_DEVICE == MCU_MSP430F5309
