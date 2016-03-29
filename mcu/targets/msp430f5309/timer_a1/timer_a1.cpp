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

#include "timer_a1.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1

#include <msp430f5309.h>
#include "../../../../error/assert.hpp"



/* =================================================================================================
	TIMER A1
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA1::TimerA1(void)
{}


/*
void yahal::mcu::targets::msp430f5309::TimerA1::setClockSource(ClockSource::Type clock_source)
{
	yahal::utility::data::setMasked<uint16_t>(TA1CTL, clock_source, 0x300);
}


void yahal::mcu::targets::msp430f5309::TimerA1::setPrescaler(Prescaler::Type prescaler)
{
	yahal::utility::data::setMasked<uint16_t>(TA1CTL, prescaler, 0x00C0);
}


void yahal::mcu::targets::msp430f5309::TimerA1::setMode(Mode::Type mode)
{
	yahal::utility::data::setMasked<uint16_t>(TA1CTL, mode, 0x0030);
}
*/

void yahal::mcu::targets::msp430f5309::TimerA1::configure(ClockSource::Type clock_source,
					  	  	  Prescaler::Type prescaler,
					  	  	  Mode::Type mode)

{
	uint16_t conf = 0;

	conf |= clock_source;	///< Select clock source
	conf |= prescaler;	///< Select clock divider
	conf |= mode;		///< Select mode
	conf |= TAIE;		///< Enable IRQ

	TA1CTL = conf;
}

/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::TimerA1::setCount(uint16_t count)
{
	TA1R = count;
}


uint16_t yahal::mcu::targets::msp430f5309::TimerA1::getCount(void) const
{
	return TA1R;
}


void yahal::mcu::targets::msp430f5309::TimerA1::setPeriod(uint16_t period)
{
	TA1CCR0 = period;
}


void yahal::mcu::targets::msp430f5309::TimerA1::reset(void)
{
	TA1CTL |= TACLR;
}

/*
void yahal::mcu::targets::msp430f5309::TimerA1::setMode(Mode::Type mode)
{
	uint16_t aux = TA1CTL;
	aux &= 0xFFCF;
	aux |= (mode << 4);
	TA1CTL = aux;
}*/

/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::TimerA1::Ccr& \
yahal::mcu::targets::msp430f5309::TimerA1::ccr(std::size_t module)
{
	assert(module == 1 || module == 2);

	switch (module) {
	case 1:
		return ccr1_;
	case 2:
		return ccr2_;
	default:
		return Ccr::Empty::instance;
	}
}


void yahal::mcu::targets::msp430f5309::TimerA1::isr(uint8_t irq)
{
	switch (irq) {
	case Irq::TIMER:
		publish(Event::OVERFLOW);
		break;
	case Irq::CCR0:
		publish(Event::PERIOD);
	case Irq::CCR1:
		ccr1_.publish(ccr1_.getOutput());
		break;
	case Irq::CCR2:
		ccr2_.publish(ccr2_.getOutput());
		break;
	default:
		break;
	}
}




/* =================================================================================================
	TIMER A1 :: CCR1
================================================================================================= */

void yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setMode(Mode::Type mode)
{
	if (mode == Mode::OFF) {
		/// DISCONNECT GPIO (input & GPIO mode)
		P2DIR &= ~1;
		P2SEL &= ~1;

		TA1CCTL1 &= 0xFF1F;		///< SET TO MODE::OUTPUT(0)
	} else {
		uint16_t aux = TA1CCTL1;
		aux &= 0xFF1F;
		aux |= (mode << 5);
		TA1CCTL1 = aux;
		P2SEL |= 1;	///< Output
		P2DIR |= 1;
	}
}


void yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setComparator(uint16_t value)
{
	TA1CCR1 = value;
}


uint16_t yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::getComparator(void) const
{
	return TA1CCR1;
}


/*void yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setOutput(bool b)
{
	b ? TA1CCTL1 |= 0x0001 : TA1CCTL1 &= ~0x0001;
}*/


bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::getOutput(void) const
{
	return TA1CCTL1 & 0x0001;
}






/* =================================================================================================
	TIMER A1 :: CCR2
================================================================================================= */

void yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setMode(Mode::Type mode)
{
	if (mode == Mode::OFF) {
		TA1CCTL2 &= 0xFF1F;		///< SET TO MODE::OUTPUT(0)
	} else {
		uint16_t aux = TA1CCTL2;
		aux &= 0xFF1F;
		aux |= (mode << 5);
		TA1CCTL2 = aux;
	}
}


void yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setComparator(uint16_t value)
{
	TA1CCR2 = value;
}


uint16_t yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::getComparator(void) const
{
	return TA1CCR2;
}


/*
void yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setOutput(bool b)
{
	b ? TA1CCTL2 |= 0x0001 : TA1CCTL2 &= ~0x0001;
}
*/

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::getOutput(void) const
{
	return TA1CCTL2 & 0x0001;
}



yahal::mcu::targets::msp430f5309::TimerA1::Ccr::Empty yahal::mcu::targets::msp430f5309::TimerA1::Ccr::Empty::instance;




/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
