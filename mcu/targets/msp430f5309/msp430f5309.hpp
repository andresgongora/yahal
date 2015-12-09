// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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




#ifndef __MCU_MSP430F5309_HPP_INCLUDED__
#define __MCU_MSP430F5309_HPP_INCLUDED__



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../../mcu_config.hpp"
#if MCU_DEVICE == MCU_MSP430F5309

#include <msp430f5309.h>




/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	MODULES
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

#include "clk/clk.hpp"
#include "wdt/wdt.hpp"
#include "gpio/gpio.hpp"
#include "i2c/i2c_master.hpp"
#include "i2c/i2c_slave.hpp"
#include "i2c/i2c_multimaster.hpp"
//#include "hal/mcu/devices/msp430f5309/i2c/i2c_master.hpp"
//#include "hal/mcu/devices/msp430f5309/i2c/i2c_slave.hpp"
//#include "hal/mcu/devices/msp430f5309/irq/irq.hpp"
//#include "hal/mcu/devices/msp430f5309/uart/uart.hpp"





/** ============================================================================================ **/
#endif	// MCU_DEVICE == MCU_MSP430F5309
#endif	// __MCU_MSP430F5309_HPP_INCLUDED__