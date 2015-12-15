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
namespace yahal{ namespace mcu{ namespace detail{
	class I2C_common;
}}}



/***********************************************************************************************//**
 * Base class for all I2C modules.
 * This virtual class implements all common elements to all I2C operation modes.
 **************************************************************************************************/
class yahal::mcu::detail::I2C_common : public yahal::mcu::detail::BaseModule
{
public:
				/**
				 * I/O operation direction
				 */
				struct Direction{ enum Type{
					READ,
					WRITE,
				};};



public:
				/**
				 * Error codes for I2C.
				 */
				struct Error{ enum Type{
					NONE = NO_ERROR,
					SLAVE_ADDRESS_NOT_7_BIT,
					SLAVE_NOT_REACHABLE,
					SLAVE_DATA_NACK,
					INVALID_MESSAGE_BUFFER,
					READ_OVERFLOW_ATTEMPT,
					ZERO_SIZE_MESSAGE,
					TRANSMISSION_PREMATURELY_ENDED,
				};};



protected:
				// VIRTUAL FUNCTIONS
	virtual void		writeBufferTX(uint8_t byte) = 0;	/**< Prepare write.*/
	virtual uint8_t		readBufferRX(void) = 0;			/**< Finish read.*/


				// CONSTRUCTOR & DESTRUCTOR
				I2C_common(void)	{}
	virtual			~I2C_common(void)	{}
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __MCU_I2C_COMMON_HPP_INCLUDED__
