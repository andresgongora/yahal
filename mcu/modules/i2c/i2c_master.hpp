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

#ifndef __YAHAL_MCU_MODULES_I2C_MASTER_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_I2C_MASTER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "../modules_namespace.hpp"
#include "i2c_common.hpp"



/***********************************************************************************************//**
 * @brief	Base class for all I2C Masters
 **************************************************************************************************/
class yahal::mcu::modules::I2CMaster : virtual public yahal::mcu::modules::details::I2CCommon
{
public:
	virtual bool 		writeRegister(	uint8_t slaveAddress,
						uint8_t registerAddress,
						uint8_t* data,
						std::size_t size) = 0;


	virtual bool 		write(	uint8_t slaveAddress,
					uint8_t* data,
					std::size_t size) = 0;


	virtual bool 		readRegister(	uint8_t slaveAddress,
						uint8_t registerAddress,
						uint8_t* data,
						std::size_t size) = 0;


	virtual bool		read(	uint8_t slaveAddress,
					uint8_t* data,
					std::size_t size) = 0;


	virtual bool 		isSlavePresent(uint8_t slaveAddress) = 0;


				// -----------------------------------------------------------------
public:
	template<typename T>
	inline bool 		writeRegister(uint8_t slaveAddr, uint8_t regAddr, T& data)
				{
					return writeRegister(	slaveAddr,
							     	regAddr,
								(uint8_t*)&data,
								sizeof(T)	);
				}

	template<typename T>
	inline bool 		write(uint8_t slaveAddr, T& data)
				{
					return write(	slaveAddr,
							(uint8_t*)&data,
							sizeof(T)	);
				}

	template<typename T>
	inline bool 		readRegister(uint8_t slaveAddr, uint8_t regAddr, T& data)
				{
					return readRegister(	slaveAddr,
								regAddr,
							    	(uint8_t*)&data,
								sizeof(T)	);
				}

	template<typename T>
	inline bool 		read(uint8_t slaveAddr, T& data)
				{
					return read(	slaveAddr,
							(uint8_t*)&data,
							sizeof(T)	);
				}
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_MCU_MODULES_I2C_MASTER_HPP_INCLUDED__
