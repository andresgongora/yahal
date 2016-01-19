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

#ifndef __YAHAL_MCU_HWEMULATION_HPP_INCLUDED__
#define __YAHAL_MCU_HWEMULATION_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../config/hwemulation/hwemulation_config.hpp"
#include "i2c/i2c_master.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	class HWEmulation;
}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::HWEmulation
{
protected:
			HWEmulation(void);

	void 		init(void);



public:
	// I2C
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
		static yahal::mcu::hwemulation::I2CMaster YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1;
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
		static yahal::mcu::hwemulation::I2CMaster YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2;
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
		static yahal::mcu::hwemulation::I2CMaster YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3;
	#endif
};



/* ---------------------------------------------------------------------------------------------- */
#endif // __YAHAL_MCU_HWEMULATION_HPP_INCLUDED__
