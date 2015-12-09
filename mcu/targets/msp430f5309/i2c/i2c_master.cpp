// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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





/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "i2c_master.hpp"
#if defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_MASTER_ENABLED__)

#include <msp430f5309.h>



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::I2C_master
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ============================================================================= INITIALIZATION **/
void mcu::targets::msp430f5309::I2C_master::doInit(void)
{
	UCB1CTL1 |= UCSWRST;			// Enable SW reset while we configure the module
	P4SEL |= BIT1 + BIT2;			// Assign I2C pins to USCI_B0

	UCB1CTL0 = UCMST | UCMODE_3 | UCSYNC;	// I2C Master, synchronous mode
	UCB1CTL1 = UCSSEL__SMCLK | UCSWRST | UCTR;	// Use SMCLK
	UCB1BRW = 12;				// fSCL = SMCLK/12 = ~100kHz TODO: CALCULATE ASKING CLK!

	UCB1CTL1 &= ~UCSWRST;			// Clear SW reset, resume operation

	UCB1IE |= UCRXIE + UCTXIE + UCNACKIE;	// Enable RX interrupt
}



/** ====================================================================== MODULE IMPLEMENTATION **/
void mcu::targets::msp430f5309::I2C_master::start(uint8_t slaveAddress, DIRECTION::type direction)
{
	while(UCB1STAT & UCBBUSY);					// Recommended to check

	if(direction == DIRECTION::WRITE)	{UCB1CTL1 |= UCTR;}	// Set transmitter
	else					{UCB1CTL1 &= ~UCTR;}	// Set receiver

	UCB1I2CSA = slaveAddress;					// Bit shifting done by HW
	UCB1CTL1 |= UCTXSTT;						// Send start
}



void mcu::targets::msp430f5309::I2C_master::stop(void)
{
	while(UCB1CTL1 & UCTXSTT);	// Wait if START in progress
	UCB1CTL1 |= UCTXSTP;
}



void mcu::targets::msp430f5309::I2C_master::writeBufferTX(uint8_t byte)
{
	UCB1TXBUF = byte;
}



uint8_t mcu::targets::msp430f5309::I2C_master::readBufferRX(void)
{
	return UCB1RXBUF;
}



void mcu::targets::msp430f5309::I2C_master::awaitTransmissionEnd(void)
{
	while(UCB1STAT & UCBBUSY);
//	UCB1CTL1 &= ~(UCTR + UCTXNACK + UCTXSTP + UCTXSTT);
}



/** ============================================================================================ **/
#endif	// defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_MASTER_ENABLED__)