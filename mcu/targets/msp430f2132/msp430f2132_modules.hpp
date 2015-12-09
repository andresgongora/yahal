// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*    AUTOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|										|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/

#ifndef __MSP430F2132_MODULES_HPP_INCLUDED__
#define __MSP430F2132_MODULES_HPP_INCLUDED__



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	NAMESPACE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace hal{ namespace uc{ namespace msp430f2132{

	class Clk;
	class Wdt;
	class Irq;

	class I2c_master;
	class I2c_slave;
}}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	MODULES
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

#include "hal/mcu/devices/msp430f2132/irq/irq.hpp"
#include "hal/mcu/devices/msp430f2132/clk/clk.hpp"
#include "hal/mcu/devices/msp430f2132/wdt/wdt.hpp"
#include "hal/mcu/devices/msp430f2132/gpio/gpio.hpp"
#include "hal/mcu/devices/msp430f2132/i2c/i2c_master.hpp"
//#include "hal/mcu/devices/msp430f2132/i2c/i2c_slave.hpp"

//#include "hal/mcu/devices/msp430f2132/uart/uart.hpp"


/** ============================================================================================ **/
#endif // __MSP430F2132_MODULES_HPP_INCLUDED__
