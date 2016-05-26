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

void yahal::mcu::targets::msp430f5309::TimerA1::configure(ClockSource::Type clock_source)
{
	TA1CTL = (TA1CTL & 0xFCFF) | clock_source;
}

void yahal::mcu::targets::msp430f5309::TimerA1::configure(Prescaler::Type prescaler)
{
	TA1CTL = (TA1CTL & 0xFF3F) | prescaler;
}

void yahal::mcu::targets::msp430f5309::TimerA1::configure(Prescaler::Type mode)
{
	// CLEAR ALL = OFF
	TA1CTL &= ~(0x0030 + TAIE);

	// IF MODE != OFF
	if(mode) { TA1CTL |= mode + TAIE; }
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

/*
void yahal::mcu::targets::msp430f5309::TimerA1::setPeriod(uint16_t period)
{
	TA1CCR0 = period;
}*/


/*void yahal::mcu::targets::msp430f5309::TimerA1::reset(void)
{
	TA1CTL |= TACLR;
}*/

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
yahal::mcu::targets::msp430f5309::TimerA1::comparator(int ccr)
{
	assert(ccr <= 2);

	switch (ccr) {
	case 0:
		return ccr0_;
	case 1:
		return ccr1_;
	case 2:
		return ccr2_;
	default:
		return Ccr::Empty::getInstance();
	}
}

/*
yahal::mcu::targets::msp430f5309::TimerA1::Comparator& \
yahal::mcu::targets::msp430f5309::TimerA1::comparator(int comparator)
{
	unsigned int ccr = comparator;
	return TimerA1::comparator(ccr);
}
*/

void yahal::mcu::targets::msp430f5309::TimerA1::isr(int irq)
{
	switch (irq)
	{
	case Irq::TIMER:
		publish(EVENT.TIMER);
		break;
	case Irq::CCR0:
		publish(EVENT.CCR0);
		break;
	case Irq::CCR1:
		publish(EVENT.CCR1);
		break;
	case Irq::CCR2:
		publish(EVENT.CCR2);
		break;
	default:
		break;
	}
}



/* =================================================================================================
	TIMER A1 :: CCR
================================================================================================= */
/*
bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr::setMode(Ccr::Mode::Type mode)
{
	return Comparator::setMode(static_cast<Comparator::Mode::Type>(mode));
}

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr::setMode(Ccr::Mode::OutputCompare::Type mode)
{
	return Comparator::setMode(static_cast<Comparator::Mode::OutputCompare::Type>(mode));
}

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr::setMode(Ccr::Mode::InputCapture::Type mode)
{
	return Comparator::setMode(static_cast<Comparator::Mode::InputCapture::Type>(mode));
}
*/


bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr::writeCctlMode(volatile uint16_t& cctl,
								   Mode::Type mode)
{
	uint16_t config = cctl;
	config &= ~(OUTMOD0 + OUTMOD1 + OUTMOD2 + CCIE);

	switch(mode)
	{
/*	case Mode::OC_NONE:
		config |= OUTMOD_0;
		break;
	case Mode::OC_SET:
		config |= OUTMOD_1;
		break;
	case Mode::OC_RESET:
		config |= OUTMOD_5;
		break;
	case Mode::OC_SET_RESET:
		config |= OUTMOD_3;
		break;
	case Mode::OC_RESET_SET:
		config |= OUTMOD_7;
		break;
	case Mode::OC_TOGGLE:
		config |= OUTMOD_4;
		break;
	case Mode::OC_TOGGLE_SET:
		config |= OUTMOD_6;
		break;
	case Mode::OC_TOGGLE_RESET:
		config |= OUTMOD_2;
		break;*/
	default:
		return false;
	}

	config |= CCIE;	// Enable IRQ
	cctl = config;	// Write configuration
	return true;
}




/* =================================================================================================
	TIMER A1 :: IRQ
================================================================================================= */

#pragma vector = TIMER1_A1_VECTOR
__interrupt void yahal::mcu::targets::msp430f5309::TimerA1::TIMER1_A1_ISR(void)
{
	switch (__even_in_range(TA1IV, 14)) {
	case 0: ///< Vector 00: No interrupts
		break;
	case 2: ///< Vector 02: CCR1
		TimerA1::getInstance().isr(TimerA1::Irq::CCR1);
		break;
	case 4: ///< Vector 04: CCR2
		TimerA1::getInstance().isr(TimerA1::Irq::CCR2);
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
		TimerA1::getInstance().isr(TimerA1::Irq::TIMER);
		break;
	default:
		break;
	}
}


#pragma vector = TIMER1_A0_VECTOR
__interrupt void yahal::mcu::targets::msp430f5309::TimerA1::TIMER1_A0_ISR(void)
{
	TimerA1::getInstance().isr(TimerA1::Irq::CCR0);
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
