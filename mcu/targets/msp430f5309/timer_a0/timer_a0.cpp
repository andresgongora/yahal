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

#include "timer_a0.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>
#include "../../../../error/assert.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::TimerA0::TimerA0(const Configuration& configuration) :
	configuration_(configuration)
{}



bool yahal::mcu::targets::msp430f5309::TimerA0::init(void)
{
	return true;
}

/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr& \
yahal::mcu::targets::msp430f5309::TimerA0::ccr(std::size_t module)
{
	switch (module) {
	case 0:
		return ccr0_;
	case 1:
		return ccr1_;
	case 2:
		return ccr2_;
	case 3:
		return ccr3_;
	case 4:
		return ccr4_;
	default:assert(false);
		return ccr0_;	///< Better return this than nothing.
	}
}



/* ---------------------------------------------------------------------------------------------- */
void yahal::mcu::targets::msp430f5309::TimerA0::Ccr0::setOutput(bool b)
{
	if (b) {
		TA0CCTL0 |= 0x0001;
	} else {
		TA0CCTL0 &= ~0x0001;
	}
}


bool yahal::mcu::targets::msp430f5309::TimerA0::Ccr0::getOutput(void)
{
	return TA0CCTL0 & 0x0001;
}


void yahal::mcu::targets::msp430f5309::TimerA0::Ccr0::setMode(Mode::Type mode)
{
	uint16_t aux = TA0CCTL0;
	aux &= 0xFF1F;
	aux |= (mode << 7);
	TA0CCTL0 = aux;
}



/* ---------------------------------------------------------------------------------------------- */
void yahal::mcu::targets::msp430f5309::TimerA0::Ccr1::setOutput(bool b)
{
	if (b) {
		TA0CCTL1 |= 0x0001;
	} else {
		TA0CCTL1 &= ~0x0001;
	}
}


bool yahal::mcu::targets::msp430f5309::TimerA0::Ccr1::getOutput(void)
{
	return TA0CCTL1 & 0x0001;
}


void yahal::mcu::targets::msp430f5309::TimerA0::Ccr1::setMode(Mode::Type mode)
{
	uint16_t aux = TA0CCTL1;
	aux &= 0xFF1F;
	aux |= (mode << 7);
	TA0CCTL1 = aux;
}



/* ---------------------------------------------------------------------------------------------- */
void yahal::mcu::targets::msp430f5309::TimerA0::Ccr2::setOutput(bool b)
{
	if (b) {
		TA0CCTL2 |= 0x0001;
	} else {
		TA0CCTL2 &= ~0x0001;
	}
}


bool yahal::mcu::targets::msp430f5309::TimerA0::Ccr2::getOutput(void)
{
	return TA0CCTL2 & 0x0001;
}


void yahal::mcu::targets::msp430f5309::TimerA0::Ccr2::setMode(Mode::Type mode)
{
	uint16_t aux = TA0CCTL2;
	aux &= 0xFF1F;
	aux |= (mode << 7);
	TA0CCTL2 = aux;
}



/* ---------------------------------------------------------------------------------------------- */
void yahal::mcu::targets::msp430f5309::TimerA0::Ccr3::setOutput(bool b)
{
	if (b) {
		TA0CCTL3 |= 0x0001;
	} else {
		TA0CCTL3 &= ~0x0001;
	}
}

bool yahal::mcu::targets::msp430f5309::TimerA0::Ccr3::getOutput(void)
{
	return TA0CCTL3 & 0x0001;
}


void yahal::mcu::targets::msp430f5309::TimerA0::Ccr3::setMode(Mode::Type mode)
{
	uint16_t aux = TA0CCTL3;
	aux &= 0xFF1F;
	aux |= (mode << 7);
	TA0CCTL3 = aux;
}




/* ---------------------------------------------------------------------------------------------- */
void yahal::mcu::targets::msp430f5309::TimerA0::Ccr4::setOutput(bool b)
{
	if (b) {
		TA0CCTL4 |= 0x0001;
	} else {
		TA0CCTL4 &= ~0x0001;
	}
}

bool yahal::mcu::targets::msp430f5309::TimerA0::Ccr4::getOutput(void)
{
	return TA0CCTL4 & 0x0001;
}


void yahal::mcu::targets::msp430f5309::TimerA0::Ccr4::setMode(Mode::Type mode)
{
	uint16_t aux = TA0CCTL4;
	aux &= 0xFF1F;
	aux |= (mode << 7);
	TA0CCTL4 = aux;
}




/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
