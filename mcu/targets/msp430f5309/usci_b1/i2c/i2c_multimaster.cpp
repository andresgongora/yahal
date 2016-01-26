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

#include "i2c_multimaster.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../../config/targets/msp430f5309/config.hpp"
#if YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true && YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER

#include "../../../../config/targets/msp430f5309/usci_b1.hpp"
#include <msp430f5309.h>


/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster	\
yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::instance_(yahal::mcu::targets::msp430f5309::config::usci_b1);

yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster&
yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::getInstance(void)
{
	return instance_;
}



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::I2CMultimaster(const Configuration& configuration) :
	configuration_(configuration)
{}



bool yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::init(void)
{
	UCB1CTL1 |= UCSWRST;				///< Enable SW reset while we configure the module
	P4SEL |= BIT1 + BIT2;				///< Assign I2C pins to USCI_B0

	UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC + UCMM;	///< I2C Master, synchronous mode, multimaster
	UCB1CTL1 = UCSSEL__SMCLK + UCSWRST + UCTR;	///< Use SMCLK
	UCB1BRW = configuration_.baud_rate_prescale;
	UCB1I2COA = configuration_.ownAddress + UCGCEN;	///< Enable general call
	UCB1CTL1 &= ~UCSWRST;				///< Clear SW reset, resume operation

	UCB1IE |= UCRXIE + UCTXIE + UCNACKIE + UCSTTIE + UCSTPIE;///< Enable Interrupts

	return true;
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::start(uint8_t slaveAddress, Direction::Type direction)
{
	while(UCB1STAT & UCBBUSY);		///< Recommended to check

	if (direction == Direction::WRITE) {
		UCB1CTL1 |= UCTR;		///< Set transmitter
	} else {
		UCB1CTL1 &= ~UCTR;		///< Set receiver
	}

	UCB1I2CSA = slaveAddress;		///< Bit shifting done by HW
	UCB1CTL1 |= UCTXSTT;			///< Send start

}



void yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::stop(void)
{
	if (not (UCB1CTL1 & UCTR)) {
		while (UCB1CTL1 & UCTXSTT);	///< Wait if START in progress during READ operation
	}

	UCB1CTL1 |= UCTXSTP;
}



void yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::writeBufferTX(uint8_t byte)
{
	UCB1TXBUF = byte;
}



uint8_t yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::readBufferRX(void)
{
	return UCB1RXBUF;
}



void yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::awaitTransmissionEnd(void)
{
	while(UCB1STAT & UCBBUSY);	///< Wait while busy

	UCB1CTL1 &= ~(UCTR + UCTXNACK + UCTXSTP + UCTXSTT);
	UCB1TXBUF = UCB1RXBUF;	// Experimental: clear both buffers
}



bool yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::isIncommingWrite(void)
{
	return (UCB1CTL1 & UCTR);
}


bool yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::isMaster(void)
{
	return (UCB1CTL0 & UCMST);
}


void yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::configureAsMaster(void)
{
	awaitTransmissionEnd();

	// I FIGURED OUT THE HARDWAY THIS IS THE ONLY WAY TO GET BACK INTO MASTER MODE
	UCB1CTL1 |= UCSWRST;						// Enter SW reset
	UCB1CTL0 |= UCMST ;						// Set as Master
	UCB1CTL1 &= ~UCSWRST;						// Return from SW Reset
	UCB1IE |= UCRXIE + UCTXIE + UCNACKIE + UCSTTIE + UCSTPIE;	// Need to reenable Irq
}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::isr(UsciB1::Irq::Type irq)
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
	case UsciB1::Irq::I2C_ARBITRATION_LOST:
		handleArbitrationLost();
		break;
	case UsciB1::Irq::I2C_NACK:
		handleReceivedNack();
		break;
	default:
		break;
	}
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_CLK_INSTANTIATE == true && YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
