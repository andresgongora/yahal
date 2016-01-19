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

#ifndef __SOFTWARE_CONFIG_HPP_INCLUDED__
#define __SOFTWARE_CONFIG_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../targets/targets.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace hwemulation{ namespace config{




/* =================================================================================================
	I2C
================================================================================================= */

#define YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE	true

#define YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1		i2c4
//#define YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2	i2c5
//#define YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3	i2c6


#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
	static const yahal::mcu::hwemulation::I2CMaster::Configuration	\
	YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1 = {
	/* sda		*/ &yahal::mcu::targets::Target::gpio[1][0],
	/* sdc		*/ &yahal::mcu::gpio[1][1],
	};
#endif
#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
	static const yahal::mcu::hwemulation::I2CMaster::Configuration	\
	YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2 = {
	/* sda		*/ &yahal::mcu::gpio[1][0],
	/* sdc		*/ &yahal::mcu::gpio[1][1],
	};
#endif
#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
	static const yahal::mcu::hwemulation::I2CMaster::Configuration	\
	YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3 = {
	/* sda		*/ &yahal::mcu::gpio[1][0],
	/* sdc		*/ &yahal::mcu::gpio[1][1],
	};
#endif



/* =================================================================================================
	X X X
================================================================================================= */




/* ---------------------------------------------------------------------------------------------- */
}}}} // namespace yahal::mcu::hwemulation::config

/* ---------------------------------------------------------------------------------------------- */
#endif // __SOFTWARE_CONFIGHPP_INCLUDED__
