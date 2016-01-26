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
#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true

#include <msp430f5309.h>
#include "../../../config/targets/msp430f5309/timer_a0.hpp"
#include "../../../../error/assert.hpp"



/* =================================================================================================
	TIMER A0
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA0	\
yahal::mcu::targets::msp430f5309::TimerA0::instance_(yahal::mcu::targets::msp430f5309::config::timer_a0);


yahal::mcu::targets::msp430f5309::TimerA0&
yahal::mcu::targets::msp430f5309::TimerA0::getInstance(void)
{
	return instance_;
}

/* ---------------------------------------------------------------------------------------------- */


yahal::mcu::targets::msp430f5309::TimerA0::TimerA0(const Configuration& configuration) :
	configuration_(configuration)
{}




bool yahal::mcu::targets::msp430f5309::TimerA0::init(void)
{
	return true;
}


void yahal::mcu::targets::msp430f5309::TimerA0::set(std::size_t value)
{
	TA0R = static_cast<uint16_t>(value);
}


std::size_t yahal::mcu::targets::msp430f5309::TimerA0::get(void) const
{
	return TA0R;
}


void yahal::mcu::targets::msp430f5309::TimerA0::reset(void) const
{
	TA0R = 0;
}


void yahal::mcu::targets::msp430f5309::TimerA0::setMode(Mode::Type mode)
{
	uint16_t aux = TA0CTL;
	aux &= 0xFFCF;
	aux |= (mode << 4);
	TA0CTL = aux;
}

/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr& \
yahal::mcu::targets::msp430f5309::TimerA0::ccr(std::size_t module)
{
	switch (module) {
	case 0:
		return Ccr0::getInstance();
	case 1:
		return Ccr1::getInstance();
	case 2:
		return Ccr2::getInstance();
	case 3:
		return Ccr3::getInstance();
	case 4:
		return Ccr4::getInstance();
	default:
		assert(false);
		return Ccr0::getInstance();;	///< TODO: Better return this than nothing.
	}
}



/* =================================================================================================
	TIMER A0 CCR0
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr0	\
yahal::mcu::targets::msp430f5309::TimerA0::Ccr0::instance_;


yahal::mcu::targets::msp430f5309::TimerA0::Ccr0&
yahal::mcu::targets::msp430f5309::TimerA0::Ccr0::getInstance(void)
{
	return instance_;
}


yahal::mcu::targets::msp430f5309::TimerA0::Ccr0::Ccr0(void)
{}

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
	aux |= (mode << 5);
	TA0CCTL0 = aux;
}



/* =================================================================================================
	TIMER A0 CCR1
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr1	\
yahal::mcu::targets::msp430f5309::TimerA0::Ccr1::instance_;


yahal::mcu::targets::msp430f5309::TimerA0::Ccr1&
yahal::mcu::targets::msp430f5309::TimerA0::Ccr1::getInstance(void)
{
	return instance_;
}


yahal::mcu::targets::msp430f5309::TimerA0::Ccr1::Ccr1(void)
{}

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
	aux |= (mode << 5);
	TA0CCTL1 = aux;
}



/* =================================================================================================
	TIMER A0 CCR2
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr2	\
yahal::mcu::targets::msp430f5309::TimerA0::Ccr2::instance_;


yahal::mcu::targets::msp430f5309::TimerA0::Ccr2&
yahal::mcu::targets::msp430f5309::TimerA0::Ccr2::getInstance(void)
{
	return instance_;
}


yahal::mcu::targets::msp430f5309::TimerA0::Ccr2::Ccr2(void)
{}

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
	aux |= (mode << 5);
	TA0CCTL2 = aux;
}



/* =================================================================================================
	TIMER A0 CCR3
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr3	\
yahal::mcu::targets::msp430f5309::TimerA0::Ccr3::instance_;


yahal::mcu::targets::msp430f5309::TimerA0::Ccr3&
yahal::mcu::targets::msp430f5309::TimerA0::Ccr3::getInstance(void)
{
	return instance_;
}


yahal::mcu::targets::msp430f5309::TimerA0::Ccr3::Ccr3(void)
{}

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
	aux |= (mode << 5);
	TA0CCTL3 = aux;
}




/* =================================================================================================
	TIMER A0 CCR4
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA0::Ccr4	\
yahal::mcu::targets::msp430f5309::TimerA0::Ccr4::instance_;


yahal::mcu::targets::msp430f5309::TimerA0::Ccr4&
yahal::mcu::targets::msp430f5309::TimerA0::Ccr4::getInstance(void)
{
	return instance_;
}


yahal::mcu::targets::msp430f5309::TimerA0::Ccr4::Ccr4(void)
{}

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
	aux |= (mode << 5);
	TA0CCTL4 = aux;
}




/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
