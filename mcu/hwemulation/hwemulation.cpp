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

#include "./hwemulation.hpp"




/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::HWEmulation::HWEmulation(void)
{}


/* ---------------------------------------------------------------------------------------------- */
void yahal::mcu::HWEmulation::init(void)
{
	// I2C
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1.init();
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2.init();
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3.init();
	#endif
}



/* ---------------------------------------------------------------------------------------------- */

//I2C
#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
		yahal::mcu::hwemulation::I2CMaster
			yahal::mcu::HWEmulation::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1
				(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1);
#endif
#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
	//		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2
	//		(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2);
#endif
#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
	//		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3
	//		(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3);
#endif



/* ---------------------------------------------------------------------------------------------- */
