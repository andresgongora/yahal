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


#include "../config/hwemulation/i2c.hpp"
#include "../config/hwemulation/uart.hpp"
#include "../config/hwemulation/etc.hpp"


#include "i2c/i2c_master.hpp"
#include "uart.hpp" etc etc


namespace yahal{
namespace mcu{


/* ---------------------------------------------------------------------------------------------- */

#ifdef yahal_mcu_hwemulation_enable_i2c
	extern asdasdsad i2c;	-> declarado en el cpp de hwemulation
#endif





/* ---------------------------------------------------------------------------------------------- */
} // namespace mcu
} // namespace yahal
#endif // __YAHAL_MCU_HWEMULATION_HPP_INCLUDED__
