// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*    AUTOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

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

#ifndef __MCU_M430F5309_I2C_SLAVE_HPP_INCLUDED__
#define __MCU_M430F5309_I2C_SLAVE_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../msp430f5309_config.hpp"
#if defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_SLAVE_ENABLED__)

#include <stdint.h>
#include <cstddef>
#include "../../../modules/i2c/i2c_slave.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace targets{ namespace msp430f5309{
	class I2C_slave;
}}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION::I2C::SLAVE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::targets::msp430f5309::I2C_slave : public mcu::I2C_slave
{
public:				// CONTRUSTOR & DESTRUCTOR
				I2C_slave(uint8_t ownAddress);


private:			// INITIALIZATION
	virtual void		doInit(void);


private:			// I2C PROTOCOL
	virtual void		writeBufferTX(uint8_t byte);
	virtual uint8_t		readBufferRX(void);
	virtual bool		isIncommingWrite(void);


private:			// PRIVATE VARIABLES
	uint8_t			_ownAddress;
};



/** ============================================================================================ **/
#endif // defined(__MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__) || defined(__MCU_MSP430F5309_I2C_SLAVE_ENABLED__)
#endif // __M430F5309_I2C_SLAVE_HPP_INCLUDED__
