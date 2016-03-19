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



#ifndef __YAHAL_MCU_MODULES_I2C_COMMON_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_I2C_COMMON_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "../modules_namespace.hpp"
#include "../base_module.hpp"
#include "../../../error/error_code.hpp"
#include "../../../rtos/rtos.hpp"



/***********************************************************************************************//**
 * @brief	Base class for all I2C modules.
 * This virtual class implements all common elements to all I2C operation modes (slave/master).
 **************************************************************************************************/
class yahal::mcu::modules::details::I2CCommon :	public yahal::error::ErrorCode
{
public:
				/// I/O operation direction
				struct Direction{ enum Type{
					READ,
					WRITE,
				};}static const DIRECTION;


				/// Error codes for I2C.
				struct Error{ enum Type{
					NO_ERROR = ErrorCode::NO_ERROR_CODE,
					SLAVE_ADDRESS_NOT_7_BIT,
					SLAVE_NOT_REACHABLE,
					SLAVE_DATA_NACK,
					INVALID_MESSAGE_BUFFER,
					READ_OVERFLOW_ATTEMPT,
					TRANSMISSION_PREMATURELY_ENDED,
				};}static const ERROR;
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_MCU_MODULES_I2C_COMMON_HPP_INCLUDED__
