// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------+-----------------------------------+
	|                                                                       |
	|             Yet Another Hardware Abstraction Layer (YAHAL)            |
	|                https://github.com/andresgongora/yahal                 |
	|                                                                       |
	|                                                                       |
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file. |
	| Machine Perception and Intelligent Robotics (MAPIR),                  |
	| University of Malaga. <http://mapir.isa.uma.es>                       |
	|                                                                       |
	| This program is free software: you can redistribute it and/or modify  |
	| it under the terms of the GNU General Public License as published by  |
	| the Free Software Foundation, either version 3 of the License, or     |
	| (at your option) any later version.                                   |
	|                                                                       |
	| This program is distributed in the hope that it will be useful,       |
	| but WITHOUT ANY WARRANTY; without even the implied warranty of        |
	| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
	| GNU General Public License for more details.                          |
	|                                                                       |
	| You should have received a copy of the GNU General Public License     |
	| along with this program. If not, see <http://www.gnu.org/licenses/>.  |
	|                                                                       |
	+-----------------------------------------------------------------------+ */


#include "msp430f5309.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309


#include "adc_10/adc_10.hpp"
#include "clk/clk.hpp"
#include "gpio/port.hpp"
#include "wdt/wdt.hpp"





/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::targets::msp430f5309::Msp430f5309::Msp430f5309(void) :
	dummy_(0)	// dummy is used in case no module is enabled
{

}


#ifdef YAHAL_MCU_MSP430F5309_ENABLE_CLK
	yahal::mcu::targets::msp430f5309::Clk
		yahal::mcu::targets::msp430f5309::Msp430f5309::clk;
#endif


#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_PORT1
	yahal::mcu::targets::msp430f5309::Port1	yahal::mcu::targets::msp430f5309::Msp430f5309::port1;
#endif


#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_WDT
	yahal::mcu::targets::msp430f5309::Wdt
		yahal::mcu::targets::msp430f5309::Msp430f5309::wdt;
#endif

/*yahal::mcu::targets::msp430f5309::Port1 yahal::mcu::targets::msp430f5309::Msp430f5309::port1;
yahal::mcu::targets::msp430f5309::Clk yahal::mcu::targets::msp430f5309::Msp430f5309::clk;
yahal::mcu::targets::msp430f5309::Wdt yahal::mcu::targets::msp430f5309::Msp430f5309::wdt;*/


/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
