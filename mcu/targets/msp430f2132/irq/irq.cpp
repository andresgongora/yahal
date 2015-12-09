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
#include <mcu/targets/msp430f2132/irq/irq.hpp>
#if MCU_DEVICE == MCU_MSP430F2132

#include <msp430f2132.h>


/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Irq
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

void hal::uc::msp430f2132::Irq::enableGlobalInterrupts(void) const
{
	_EINT();
}


void hal::uc::msp430f2132::Irq::disableGlobalInterrupts(void) const
{
	_DINT();
}





/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Irq :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace hal{namespace uc{namespace msp430f2132{
	hal::uc::msp430f2132::Irq irq;
}}}




/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	INTERRUPT SERVICE ROUTINES
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	// NACK IRQ
	if((UCB0STAT & UCNACKIFG) && (IE2 & UCB0RXIE))//(UCB0I2CIE & UCNACKIE))
	{
		UCB0STAT &= ~UCNACKIFG;			// Disable FLAG
		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::I2C::RECEIVED_NACK);
	}

	// START IRQ
	else if((UCB0STAT & UCSTTIFG) && (IE2 & UCB0RXIE))//(UCB0I2CIE & UCSTTIE))
	{
		UCB0STAT &= ~UCSTTIFG;			// Clear FLAG
		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::I2C::RECEIVED_START);
	}

	//RX SPI
	if((IFG2 & UCA0RXIFG) && (IE2 & UCA0RXIE))
	{
		IFG2 &= ~UCA0RXIFG;
		hal::uc::msp430f2132::irq.uart.publish(hal::uc::Irq::UART::RX);
	}
}


#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if((IFG2 & UCB0TXIFG) && (IE2 & UCB0TXIE))				// I2C TX /////////////////
	{
		IFG2 &= ~UCB0TXIFG;
		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::I2C::TX_BUFFER_EMPTY);
	}

	// RX IRQ
	else if((IFG2 & UCB0RXIFG) && (IE2 & UCB0TXIE ))
	{
//		IE2  &= ~UCB0RXIE;		// Disable Interrupt
		IFG2 &= ~UCB0RXIFG;		// Clear flag

		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::I2C::RX_BUFFER_FULL);

//		IE2  |= UCB0RXIE;		// Enable Interrupt
	}

	//TX SPI
	if((IFG2 & UCA0TXIFG) && (IE2 & UCA0TXIE))
	{
		IFG2 &= ~UCA0TXIFG;
		hal::uc::msp430f2132::irq.uart.publish(hal::uc::Irq::UART::TX);
	}
}


/** ============================================================================================ **/
#endif // MCU_DEVICE == MCU_MSP430F2132
