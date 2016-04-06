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


#include "adc_10.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_ADC_10

#include <msp430f5309.h>


/* ---------------------------------------------------------------------------------------------- */

yahal::utility::oop::ServiceLocator<yahal::mcu::modules::details::IsrHandler>\
	yahal::mcu::targets::msp430f5309::irq::Adc10::adc_10_(yahal::mcu::modules::details::IsrHandler::Empty::getInstance());



#pragma vector = ADC10_VECTOR
__interrupt void yahal::mcu::targets::msp430f5309::irq::Adc10::ADC_10_ISR(void)
{
	switch(__even_in_range(ADC10IV,12)) {
	case  0: ///< Vector 00: No interrupts
		break;
	case  2: ///< Vector 02: Overflow
		adc_10_.get().isr(Adc10::Irq::OVERFLOW);
		break;
	case  4: ///< Vector 04: Over sample
		adc_10_.get().isr(Adc10::Irq::OVERSAMPLE);
		break;
	case  6: ///< Vector 06: Signal over threshold high level
		adc_10_.get().isr(Adc10::Irq::THRESHOLD_OVER);
		break;
	case  8: ///< Vector 08: Signal below threshold low level
		adc_10_.get().isr(Adc10::Irq::THRESHOLD_BELOW);
		break;
	case 10: ///< Vector 10: Signal inside threshold levels
		adc_10_.get().isr(Adc10::Irq::THRESHOLD_INSIDE);
		break;
	case 12: ///< Vector 12: ADC convertion end
		adc_10_.get().isr(Adc10::Irq::CONVERTION);
		break;
	default:
		break;
	}
}


/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_ADC_10
