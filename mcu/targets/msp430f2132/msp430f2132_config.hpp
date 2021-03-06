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




#ifndef __MSP430F2132_CONFIG_HPP_INCLUDED__
#define __MSP430F2132_CONFIG_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../targets/msp430f2132/msp430f2132.hpp"
#if YAHAL_MCU_TARGET == MCU_MSP430F2132



/* ============================================================================================== */
 *	CONFIGURATION
 * ============================================================================================== */

#define __MSP430F2132_CLK_ENABLED__
#define __MSP430F2132_WDT_ENABLED__
#define __MSP430F2132_GPIO_ENABLED__
#define __MSP430F2132_I2C_MASTER_ENABLED__


/* ---------------------------------------------------------------------------------------------- */
#endif // MCU_DEVICE == MCU_MSP430F2132
#endif //__MSP430F2132_CONFIGHPP_INCLUDED__
