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



#ifndef __MCU_I2C_COMMON_HPP_INCLUDED__
#define __MCU_I2C_COMMON_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "../base_module.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	class I2C_common;
}



/* ============================================================================================== */
 *	yahal::mcu::I2C_master
 * ============================================================================================== */

class yahal::mcu::I2C_common : public yahal::mcu::BaseModule
{
public:				// CONFIGURATION VALUES
				struct DIRECTION{ enum type{
					READ,
					WRITE,
				};};



public:				// ERROR CODE
				struct ERROR{ enum type{
					NONE = NO_ERROR,

					NOT_INITIALIZED = 10,

					SLAVE_ADDRESS_NOT_7_BIT =21,
					SLAVE_NOT_REACHABLE = 22,
					SLAVE_DATA_NACK = 23,

					INVALID_MESSAGE_BUFFER = 31,
					READ_OVERFLOW_ATTEMPT = 32,
					ZERO_SIZE_MESSAGE = 33,

					TRANSMISSION_PREMATURELY_ENDED = 41,

				};};


protected:			// I2C PROTOCOL -> IMPLEMENT
	virtual void		writeBufferTX(uint8_t byte) = 0;
	virtual uint8_t		readBufferRX(void) = 0;



protected:			// CONSTRUCTOR & DESTRUCTOR
				I2C_common(void)	{}
	virtual			~I2C_common(void)	{}
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __MCU_I2C_COMMON_HPP_INCLUDED__
