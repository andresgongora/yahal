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

#ifndef __YAHAL_MCU_CONFIG_TARGETS_MSP430F5309_TIMER_A0_HPP_INCLUDED__
#define __YAHAL_MCU_CONFIG_TARGETS_MSP430F5309_TIMER_A0_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "config.hpp"
#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true

#include "../../../targets/msp430f5309/timer_a0/timer_a0.hpp"



namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{ namespace config{
/* ---------------------------------------------------------------------------------------------- */


const yahal::mcu::targets::msp430f5309::TimerA0::Configuration timer_a0 = {
/* clock_source		*/ TimerA0::ClockSource::SMCLK,
/* divider		*/ TimerA0::Divider::DIVIDER_1,
/* mode			*/ TimerA0::Mode::CONTINUOUS,
/* ccr0_output_enable	*/ false,
/* ccr1_output_enable	*/ false,
/* ccr2_output_enable	*/ false,
/* ccr3_output_enable	*/ false,
/* ccr4_output_enable	*/ false,
};



/* ---------------------------------------------------------------------------------------------- */
}}}}}	// namespace yahal::mcu::targets::msp430f5309::config
#endif // YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
#endif // __YAHAL_MCU_CONFIG_TARGETS_MSP430F5309_TIMER_A0_HPP_INCLUDED__
