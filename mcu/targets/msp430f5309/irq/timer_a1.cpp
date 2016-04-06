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


#include "timer_a1.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1

#include <msp430f5309.h>


/* ---------------------------------------------------------------------------------------------- */

yahal::utility::oop::ServiceLocator<yahal::mcu::modules::details::IsrHandler>\
	yahal::mcu::targets::msp430f5309::irq::TimerA1::timer_a1_(yahal::mcu::modules::details::IsrHandler::Empty::getInstance());


#pragma vector = TIMER1_A1_VECTOR
__interrupt void yahal::mcu::targets::msp430f5309::irq::TimerA1::TIMER1_A1_ISR(void)
{
	switch (__even_in_range(TA1IV, 14)) {
	case 0: ///< Vector 00: No interrupts
		break;
	case 2: ///< Vector 02: CCR1
		timer_a1_.get().isr(TimerA1::Irq::CCR1);
		break;
	case 4: ///< Vector 04: CCR2
		timer_a1_.get().isr(TimerA1::Irq::CCR2);
		break;
	case 6: ///< Vector 06: reserved
		break;
	case 8: ///< Vector 08: reserved
		break;
	case 10: ///< Vector 10: reserved
		break;
	case 12: ///< Vector 12: reserved
		break;
	case 14: ///< Vector 14: TA1
		timer_a1_.get().isr(TimerA1::Irq::TIMER);
		break;
	default:
		break;
	}
}


#pragma vector = TIMER1_A0_VECTOR
__interrupt void yahal::mcu::targets::msp430f5309::irq::TimerA1::TIMER1_A0_ISR(void)
{
	timer_a1_.get().isr(TimerA1::Irq::CCR0);
}


/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
