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




#ifndef __MCU_M430F5309_I2C_MASTER_HPP_INCLUDED__
#define __MCU_M430F5309_I2C_MASTER_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../msp430f5309_config.hpp"
#if defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_MASTER_ENABLED__)

#include <stdint.h>
#include <cstddef>
#include "../../../modules/i2c/i2c_master.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace targets{ namespace msp430f5309{
	class I2C_master;
}}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::msp430f5309::I2C_master
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::targets::msp430f5309::I2C_master : public mcu::I2C_master
{
private:			// INITIALIZATION
	virtual void		doInit(void);



private:			// MODULE IMPLEMENTATION
	virtual void		start(uint8_t slaveAddress, DIRECTION::type direction);
	virtual void		stop(void);
	virtual void		writeBufferTX(uint8_t byte);
	virtual uint8_t		readBufferRX(void);
	virtual void		awaitTransmissionEnd(void);
};



/** ============================================================================================ **/
#endif	// defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_MASTER_ENABLED__)
#endif	// __MCU_M430F5309_I2C_MASTER_HPP_INCLUDED__
