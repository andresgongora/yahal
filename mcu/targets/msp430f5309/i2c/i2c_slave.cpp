// 1 TAB = 8 SPACES //

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "i2c_slave.hpp"
#if defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_SLAVE_ENABLED__)

#include <msp430f5309.h>



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DEFINITION::M430F5309_I2C_SLAVE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ============================================================================= INITIALIZATION **/

mcu::targets::msp430f5309::I2C_slave::I2C_slave(uint8_t ownAddress) :
	_ownAddress(ownAddress)
{

}



void mcu::targets::msp430f5309::I2C_slave::doInit(void)
{
	UCB1CTL1 |= UCSWRST;				// Enable SW reset

	P4SEL |= 0x06;					// Config GPIO pins
	UCB1CTL1 = UCSSEL__SMCLK + UCSWRST;		// SMCLK clock source (keep SW reset)
	UCB1CTL0 = UCMODE_3 + UCSYNC;			// I2C mode + syncrhonous
	UCB1I2COA = _ownAddress;			// Set own slave address
	UCB1CTL1 &= ~UCSWRST;				// Clear SW Reset

	UCB1IE |= UCTXIE + UCRXIE + UCSTTIE + UCSTPIE;	// Enable IE
}



/** =============================================================================== I2C PROTOCOL **/
void mcu::targets::msp430f5309::I2C_slave::writeBufferTX(uint8_t byte)
{
	UCB1TXBUF = byte;
}



uint8_t mcu::targets::msp430f5309::I2C_slave::readBufferRX(void)
{
	return UCB1RXBUF;
}



bool mcu::targets::msp430f5309::I2C_slave::isIncommingWrite(void)
{
	return (UCB1CTL1 & UCTR);
}



/** ============================================================================================ **/
#endif	// defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_SLAVE_ENABLED__)
