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
#include <mcu/targets/msp430f2132/i2c/i2c_master.hpp>
#ifdef __MSP430F2132_I2C_MASTER_ENABLED__

#include <msp430f2132.h>
#include "hal/mcu/virtual/irq/irq.hpp"
#include "hal/mcu/devices/msp430f2132/irq/irq.hpp"



/* ============================================================================================== */
 *	DEFINITION::M430F2132_I2C_MASTER
 * ============================================================================================== */

/** ============================================================================= INITIALIZATION **/

bool hal::uc::msp430f2132::I2c_master::init(uint8_t ownAddress)
{
	UCB0CTL1 |= UCSWRST;        		// Disable I2C module while configuring


	// GPIO CONFIGURATION
	P3SEL |= 0x06;				// Use P3.1 and P3.2 for I2C

	// CONFIGURATION
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;	// Master, I2C, Syncronous
	UCB0CTL1 = UCSSEL_2 + UCTR + UCSWRST;	// Use SMCLK as clock. Start in TX mode. Hold in SW reset

	// CLOCK PRESCALE
	UCB0BR0 = 20;
	UCB0BR1 = 0;

	// OWN ADDRESS
	UCB0I2COA = ownAddress;			// Own adress. General call response disabled
	UCB0I2CSA = 0;				// Slave address to write to. Set to 0 for now.


	UCB0CTL1 &= ~UCSWRST;			// Clear SW reset, resume operation


	// IRQ
	UCB0I2CIE |= UCNACKIE;			// IRQ for: nack
	IFG2&= ~(UCB0TXIFG + UCB0RXIFG);	// Clear IRQ flags
	IE2 |= UCB0RXIE + UCB0TXIE;             // Enable RX IRQ and TX IRQ
	msp430f2132::irq.i2c.subscribe(*this);	// Subscribe to IRQ notifications


	setErrorCode(Error::NO_ERROR);
	setInitialized();
	return true;
}



/** =============================================================================== I2C PROTOCOL **/

void hal::uc::msp430f2132::I2c_master::start(uint8_t slaveAddress, DIRECTION::Type direction)
{
	if(direction == DIRECTION::WRITE)	{UCB0CTL1 |= UCTR;}
	else					{UCB0CTL1 &= ~UCTR;}

	UCB0I2CSA = slaveAddress;		// Bit shifting done by HW
	UCB0CTL1 |= UCTXSTT;			// Send start
}


/*void hal::uc::msp430f2132::I2c_master::stopAfterFirstRXByte(void)
{
	while(UCB0CTL1 & UCTXSTT);	// Wait for START to end. TODO: WARNING: POLLING INSIDE IRQ
	UCB0CTL1 |= UCTXSTP;		// Send stop as soon as first byte has been received
}*/

void 	hal::uc::msp430f2132::I2c_master::stop(void)
{
	while(UCB0CTL1 & UCTXSTT);	// Wait if START in progress
	UCB0CTL1 |= UCTXSTP;
}

//void 	hal::uc::msp430f2132::I2c_master::sendNack(void)		{UCB0CTL1 |= UCTXNACK;}	// Automatically cleared

void 	hal::uc::msp430f2132::I2c_master::writeBufferTX(uint8_t byte)	{UCB0TXBUF = byte;}
uint8_t	hal::uc::msp430f2132::I2c_master::readBufferRX(void)		{return UCB0RXBUF;}





void hal::uc::msp430f2132::I2c_master::awaitTransmissionEnd(void)
{
	while(UCB0STAT & UCBBUSY);
	UCB0CTL1 &= ~(UCTR + UCTXNACK + UCTXSTP + UCTXSTT);
}




void hal::uc::msp430f2132::I2c_master::notify(hal::uc::Irq::I2C::Type message)
{
	switch(message)
	{
	case Irq::I2C::TX_BUFFER_EMPTY:
		bufferTXEmpty();
		break;

	case Irq::I2C::RX_BUFFER_FULL:
		bufferRXFull();
		break;

	case Irq::I2C::RECEIVED_NACK:
		receivedNack();
		break;

	default:break;
	}
}




/* ============================================================================================== */
 *	hal::uc::msp430f2132::I2c_master :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	hal::uc::msp430f2132::I2c_master i2c_master;
}}}



/* ---------------------------------------------------------------------------------------------- */
#endif // __MSP430F2132_I2C_MASTER_ENABLED__
