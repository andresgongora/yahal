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


#ifndef __YAHAL_MCU_MSP430F5309_NAMESPACE_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_NAMESPACE_HPP_INCLUDED__


#include "../../config/config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309


#include <stdint.h>
#include <msp430f5309.h>


namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{

		class Msp430f5309;

		class Clk;
		class Wdt;


		template<volatile uint8_t& T_DIR,
			 volatile uint8_t& T_OUT,
			 volatile uint8_t& T_IN,
			 volatile uint8_t& T_REN>
		class Port;


		typedef Port<P1DIR, P1OUT, P1IN, P1REN> Port1;
		typedef Port<P2DIR, P2OUT, P2IN, P2REN> Port2;
		typedef Port<P3DIR, P3OUT, P3IN, P3REN> Port3;
		typedef Port<P3DIR, P3OUT, P3IN, P3REN> Port4;
		typedef Port<P3DIR, P3OUT, P3IN, P3REN> Port5;
		typedef Port<P3DIR, P3OUT, P3IN, P3REN> Port6;

}}}} // namespace yahal::mcu::targets::msp430f5309



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif	// __YAHAL_MCU_MSP430F5309_NAMESPACE_HPP_INCLUDED__
