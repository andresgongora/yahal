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

#ifndef __YAHAL_MCU_EMPTY_I2C_MASTER_HPP_INCLUDED__
#define __YAHAL_MCU_EMPTY_I2C_MASTER_HPP_INCLUDED__


#include "../empty_namespace.hpp"
#include "../../modules/i2c/i2c_master.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace empty{
	class I2CMaster;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::empty::I2CMaster : public yahal::mcu::modules::I2CMaster
{
public:
	virtual bool 		writeRegister(	uint8_t slaveAddress,
						uint8_t registerAddress,
						uint8_t* data,
						std::size_t size) {
					return true;
				}


	virtual bool 		write(	uint8_t slaveAddress,
					uint8_t* data,
					std::size_t size) {
					return true;
				}


	virtual bool 		readRegister(	uint8_t slaveAddress,
						uint8_t registerAddress,
						uint8_t* data,
						std::size_t size) {
					return true;
				}


	virtual bool		read(	uint8_t slaveAddress,
					uint8_t* data,
					std::size_t size) {
					return true;
				}


	virtual bool 		isSlavePresent(uint8_t slaveAddress) {
					return true;
				}
};



/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_MCU_MSP430F5309_I2C_MASTER_HPP_INCLUDED__
