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

#include <mcu/targets/msp430f5309/adc_10/adc_10.hpp>
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309
#if YAHAL_MCU_MSP430F5309_ADC_10_INSTANTIATE == true

#include <msp430f5309.h>
#include "../../../config/targets/msp430f5309/adc_10.hpp"



/* =================================================================================================
	TIMER A1
================================================================================================= */

yahal::mcu::targets::msp430f5309::Adc10	\
yahal::mcu::targets::msp430f5309::Adc10::instance_(yahal::mcu::targets::msp430f5309::config::adc_10);


yahal::mcu::targets::msp430f5309::Adc10&
yahal::mcu::targets::msp430f5309::Adc10::getInstance(void)
{
	return instance_;
}

/* ---------------------------------------------------------------------------------------------- */


yahal::mcu::targets::msp430f5309::Adc10::Adc10(const Configuration& configuration) :
	configuration_(configuration)
{}




bool yahal::mcu::targets::msp430f5309::Adc10::init(void)
{
	uint16_t conf = 0;


	return true;
}

/* ---------------------------------------------------------------------------------------------- */



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::Adc10::isr(Irq::Type irq)
{
	switch (irq) {

	default:
		break;
	}
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ADC_10_INSTANTIATE == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
