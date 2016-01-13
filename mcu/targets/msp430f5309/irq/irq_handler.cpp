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

#include <targets/msp430f5309/irq/irq_handler.hpp>
#if MCU_DEVICE == MCU_MSP430F5309

#include <msp430f5309.h>



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::IRQHandler::IRQHandler(void) :
	p_i2c_(NULL)
{}


void yahal::mcu::targets::msp430f5309::IRQHandler::doInit(void)
{}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::IRQHandler::enableGlobalInterrupts(void) const
{}


void yahal::mcu::targets::msp430f5309::IRQHandler::disableGlobalInterrupts(void) const
{}



/* ---------------------------------------------------------------------------------------------- */


void yahal::mcu::targets::msp430f5309::IRQHandler::setISRHandlerI2C(I2C* p_handler)
{
	p_i2c_ = p_handler;
}



void yahal::mcu::targets::msp430f5309::IRQHandler::irqHandleI2C(I2C::IRQ::Type irq)
{
	if (p_i2c_) {
		p_i2c_->isr(irq);
	}
}

/* ---------------------------------------------------------------------------------------------- */



#ifdef asd
/* ============================================================================================== */
 *	hal::uc::msp430f2132::Irq
 * ============================================================================================== */

void hal::uc::msp430f2132::Irq::enableGlobalInterrupts(void) const
{
	_EINT();
}


void hal::uc::msp430f2132::Irq::disableGlobalInterrupts(void) const
{
	_DINT();
}





/* ============================================================================================== */
 *	hal::uc::msp430f2132::Irq :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	hal::uc::msp430f2132::Irq irq;
}}}




/* ============================================================================================== */
 *	INTERRUPT SERVICE ROUTINES
 * ============================================================================================== */

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	// NACK IRQ
	if((UCB0STAT & UCNACKIFG) && (IE2 & UCB0RXIE))//(UCB0I2CIE & UCNACKIE))
	{
		UCB0STAT &= ~UCNACKIFG;			// Disable FLAG
		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::Code::I2C::NACK);
	}

	// START IRQ
	else if((UCB0STAT & UCSTTIFG) && (IE2 & UCB0RXIE))//(UCB0I2CIE & UCSTTIE))
	{
		UCB0STAT &= ~UCSTTIFG;			// Disable FLAG
		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::Code::I2C::START);
	}

	//RX SPI
	if((IFG2 & UCA0RXIFG) && (IE2 & UCA0RXIE))
	{
		IFG2 &= ~UCA0RXIFG;
		hal::uc::msp430f2132::irq.uart.publish(hal::uc::Irq::Code::UART::RX);
	}
}


#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if((IFG2 & UCB0TXIFG) && (IE2 & UCB0TXIE))				// I2C TX /////////////////
	{
		IFG2 &= ~UCB0TXIFG;
		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::Code::I2C::TX);
	}

	// RX IRQ
	else if((IFG2 & UCB0RXIFG) && (IE2 & UCB0TXIE ))
	{
		IFG2 &= ~UCB0RXIFG;
		hal::uc::msp430f2132::irq.i2c.publish(hal::uc::Irq::Code::I2C::RX);
	}

	//TX SPI
	if((IFG2 & UCA0TXIFG) && (IE2 & UCA0TXIE))
	{
		IFG2 &= ~UCA0TXIFG;
		hal::uc::msp430f2132::irq.uart.publish(hal::uc::Irq::Code::UART::TX);
	}
}





/* ---------------------------------------------------------------------------------------------- */
#endif // MCU_DEVICE == MCU_MSP430F5309
#endif
