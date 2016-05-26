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




#ifndef __M430F2132_I2C_SLAVE_HPP_INCLUDED__
#define __M430F2132_I2C_SLAVE_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "hal/mcu/virtual/i2c/i2c_slave.hpp"
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"



/** --- DEFINE --------------------------------------------------------------------------------- **/

/* ============================================================================================== */
 *	DECLARATION::I2C::SLAVE
 * ============================================================================================== */

class hal::uc::msp430f2132::I2c_slave : public hal::uc::I2CSlave
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


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__M430F2132_I2C_SLAVE_HPP_INCLUDED__
