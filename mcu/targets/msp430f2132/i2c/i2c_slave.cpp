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
#include <hal/error/error_code.hpp>
#include <mcu/targets/msp430f2132/i2c/i2c_slave.hpp>
#include <msp430f2132.h>


/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DEFINITION::M430F2132_I2C_SLAVE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ============================================================================= INITIALIZATION **/

bool hal::uc::msp430f2132::I2c_slave::init(uint8_t module, uint8_t ownAddress)
{
	// SELECT MODULE -> This MCU has only 1 I2C module
	if(module != 0)
	{
		setErrorCode(error_moduleDoesNotExist);
		return false;
	}


	UCB0CTL1 |= UCSWRST;        		// Disable I2C module while configuring


	// GPIO CONFIGURATION
	P3SEL |= 0x06;				// Use P3.1 and P3.2 for I2C

	// CONFIGURATION
	UCB0CTL0 = UCMODE_3 + UCSYNC;		// Master, I2C, Syncronous

	// CLOCK PRESCALE
	UCB0BR0 = 80;
	UCB0BR1 = 0;

	// OWN ADDRESS
	UCB0I2COA = ownAddress;			// Own adress. General call response disabled


	UCB0CTL1 &= ~UCSWRST;			// Clear SW reset, resume operation


	// IRQ
	UCB0I2CIE |= UCSTTIE;			// Enable Start interrupt
	IFG2&= ~(UCB0TXIFG + UCB0RXIFG);	// Clear IRQ flags
	IE2 |= UCB0RXIE + UCB0TXIE;             // Enable RX IRQ and TX IRQ


	setErrorCode(noError);
	setInitialized();
	return true;
}


/** =============================================================================== I2C PROTOCOL **/

void 	hal::uc::msp430f2132::I2c_slave::sendByte(uint8_t byte)	{UCB0TXBUF = byte;}
uint8_t hal::uc::msp430f2132::I2c_slave::receiveByte(void)	{return UCB0RXBUF;}
bool 	hal::uc::msp430f2132::I2c_slave::isIncommingWrite(void)	{return (!(UCB0CTL1 & UCTR));}


/** ============================================================================================ **/
