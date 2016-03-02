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



#ifndef __YAHAL_MCU_MODULES_I2C_COMMON_MANAGER_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_I2C_COMMON_MANAGER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "../../../../rtos/rtos.hpp"
#include "../i2c_common.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{ namespace details{
	class I2CCommonManager;
}}}}



/***********************************************************************************************//**
 * @brief	Base class for all I2C modules.
 * This virtual class implements all common elements to all I2C operation modes (slave/master).
 **************************************************************************************************/
class yahal::mcu::modules::details::I2CCommonManager :
	virtual public yahal::mcu::modules::details::I2CCommon
{
protected:
				/// Prepare module for exclusive operation.
	void			open(void){
					mutex_.lock();
					clearErrorCode();
				}

				/// Releases module
	void			close(void){
					mutex_.unlock();
				}


				/// Write to output buffer. Let HW handle TX.
	virtual void		writeBufferTX(uint8_t byte) = 0;


				/// Read input buffer.
	virtual uint8_t		readBufferRX(void) = 0;


private:
	yahal::rtos::Mutex	mutex_;	///< Mutex for exclusive access to each derived module
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_MCU_MODULES_I2C_COMMON_MANAGER_HPP_INCLUDED__
