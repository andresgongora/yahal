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

	///TODO: Use a flag to enable TX and RX, and check if thos eare enabled when calling IRQ routines. User may call them by accident

#ifndef __YAHAL_MCU_MODULES_I2C_MULTIMASTER_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_I2C_MULTIMASTER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "i2c_master.hpp"
#include "i2c_slave.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{
	class I2CMultimaster;
}}}




/***********************************************************************************************//**
 * @brief	I2C Multimaster base class.
 * 	Inherits from I2CMaster and I2CSlave.
 **************************************************************************************************/
class yahal::mcu::modules::I2CMultimaster :
	public yahal::mcu::modules::I2CMaster,
	public yahal::mcu::modules::I2CSlave
{
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_MCU_MODULES_I2C_MULTIMASTER_HPP_INCLUDED__
