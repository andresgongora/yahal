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


#include "gpio/port.hpp"


namespace yahal{
namespace mcu{
/* ---------------------------------------------------------------------------------------------- */


// GPIO
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT1
	yahal::mcu::targets::msp430f5309::Port1& port1 =
			yahal::mcu::targets::msp430f5309::Port1::getInstance();
#endif
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT2
	yahal::mcu::targets::msp430f5309::Port2& port2 =
			yahal::mcu::targets::msp430f5309::Port2::getInstance();
#endif
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT3
	yahal::mcu::targets::msp430f5309::Port3& port3 =
			yahal::mcu::targets::msp430f5309::Port3::getInstance();
#endif
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT4
	yahal::mcu::targets::msp430f5309::Port4& port4 =
			yahal::mcu::targets::msp430f5309::Port4::getInstance();
#endif
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT5
	yahal::mcu::targets::msp430f5309::Port5& port5 =
			yahal::mcu::targets::msp430f5309::Port5::getInstance();
#endif
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT6
	yahal::mcu::targets::msp430f5309::Port6& port6 =
			yahal::mcu::targets::msp430f5309::Port6::getInstance();
#endif



/* ---------------------------------------------------------------------------------------------- */
} //namespace yahal
} //namespace mcu







/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::targets::msp430f5309::Msp430f5309::Msp430f5309(void) :

	// ADC_10
	#ifdef YAHAL_MCU_MSP430F5309_ENABLE_ADC_10
		adc_10(yahal::mcu::targets::msp430f5309::Adc10 adc_10),
	#endif


	// CLK
	#ifdef YAHAL_MCU_MSP430F5309_ENABLE_CLK
		clk(yahal::mcu::targets::msp430f5309::Clk::getInstance()),
	#endif

/*
	// GPIO
	#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT1
		port1(yahal::mcu::targets::msp430f5309::Port1::getInstance()),
	#endif
*/

	// TIMER_A1
	//#ifdef YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
	//	timer_a1(yahal::mcu::targets::msp430f5309::TimerA1::getInstance()),
	//#endif


	// WDT
	#ifdef YAHAL_MCU_MSP430F5309_ENABLE_WDT
		wdt(yahal::mcu::targets::msp430f5309::Wdt::getInstance()),
	#endif


	dummy(0)	// dummy is used in case no module is enabled
{}



/* ---------------------------------------------------------------------------------------------- */
bool yahal::mcu::targets::msp430f5309::Msp430f5309::init(void)
{
	return true;
}// init



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
