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

#ifndef __M430F2132_I2C_SLAVE_HPP_INCLUDED__
#define __M430F2132_I2C_SLAVE_HPP_INCLUDED__



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "hal/mcu/virtual/i2c/i2c_slave.hpp"
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"



/** --- DEFINE --------------------------------------------------------------------------------- **/

/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION::I2C::SLAVE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class hal::uc::msp430f2132::I2c_slave : public hal::uc::I2C_slave
{
public:
				// INITIALIZATION
	bool			init(uint8_t module = 0, uint8_t ownAddress = I2C_DEFAULT_OWN_ADDR);


private:
				// I2C PROTOCOL
	void			sendByte(uint8_t byte);
	uint8_t			receiveByte(void);
	bool			isIncommingWrite(void);


};


/** ============================================================================================ **/
#endif 	//__M430F2132_I2C_SLAVE_HPP_INCLUDED__
