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
#include "i2c_multimaster.hpp"
#ifdef __MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__

#include <msp430f5309.h>



/* ============================================================================================== */
 *	yahal::mcutargets::msp430f5309::I2C_multimaster
 * ============================================================================================== */

/** ================================================================================ CONSTRUCTOR **/
yahal::mcutargets::msp430f5309::I2C_multimaster::I2C_multimaster(uint8_t ownAddress) :
	_ownAddress(ownAddress)
{}



/** ============================================================================= INITIALIZATION **/
void yahal::mcutargets::msp430f5309::I2C_multimaster::doInit(void)
{
	UCB1CTL1 |= UCSWRST;				// Enable SW reset while we configure the module
	P4SEL |= BIT1 + BIT2;				// Assign I2C pins to USCI_B0

	UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC + UCMM;	// I2C Master, synchronous mode, multimaster
	UCB1CTL1 = UCSSEL__SMCLK + UCSWRST + UCTR;	// Use SMCLK
	UCB1BRW = 32;					// fSCL = SMCLK/12 = ~100kHz TODO: CALCULATE ASKING CLK!
	UCB1I2COA = _ownAddress + UCGCEN;
	UCB1CTL1 &= ~UCSWRST;				// Clear SW reset, resume operation

	UCB1IE |= UCRXIE + UCTXIE + UCNACKIE + UCSTTIE + UCSTPIE;			// Enable Interrupts
}



/** ====================================================================== MODULE IMPLEMENTATION **/

void yahal::mcutargets::msp430f5309::I2C_multimaster::start(uint8_t slaveAddress, DIRECTION::Type direction)
{
	while(UCB1STAT & UCBBUSY);					// Recommended to check

	if(direction == DIRECTION::WRITE)	{UCB1CTL1 |= UCTR;}	// Set transmitter
	else					{UCB1CTL1 &= ~UCTR;}	// Set receiver

	UCB1I2CSA = slaveAddress;					// Bit shifting done by HW
	UCB1CTL1 |= UCTXSTT;						// Send start

}



void yahal::mcutargets::msp430f5309::I2C_multimaster::stop(void)
{
	if(not(UCB1CTL1 & UCTR))
	{
		while(UCB1CTL1 & UCTXSTT);	// Wait if START in progress during READ operation
	}
	UCB1CTL1 |= UCTXSTP;
}



void yahal::mcutargets::msp430f5309::I2C_multimaster::writeBufferTX(uint8_t byte)
{
	UCB1TXBUF = byte;
}



uint8_t yahal::mcutargets::msp430f5309::I2C_multimaster::readBufferRX(void)
{
	return UCB1RXBUF;
}



void yahal::mcutargets::msp430f5309::I2C_multimaster::awaitTransmissionEnd(void)
{
	while(UCB1STAT & UCBBUSY);
	UCB1CTL1 &= ~(UCTR + UCTXNACK + UCTXSTP + UCTXSTT);
	UCB1TXBUF = UCB1RXBUF;	// Experimental: clear both buffers
}



bool yahal::mcutargets::msp430f5309::I2C_multimaster::isIncommingWrite(void)
{
	return (UCB1CTL1 & UCTR);
}


bool yahal::mcutargets::msp430f5309::I2C_multimaster::isMaster(void)
{
	return (UCB1CTL0 & UCMST);
}


void yahal::mcutargets::msp430f5309::I2C_multimaster::configureAsMaster(void)
{
	awaitTransmissionEnd();

	// I FIGURED OUT THE HARDWAY THIS IS THE ONLY WAY TO GET BACK INTO MASTER MODE
	UCB1CTL1 |= UCSWRST;						// Enter SW reset
	UCB1CTL0 |= UCMST ;						// Set as Master
	UCB1CTL1 &= ~UCSWRST;						// Return from SW Reset
	UCB1IE |= UCRXIE + UCTXIE + UCNACKIE + UCSTTIE + UCSTPIE;	// Need to reenable IRQ
}



/* ---------------------------------------------------------------------------------------------- */
#endif	// __MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__
