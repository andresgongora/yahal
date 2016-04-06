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

	// CONFIGURE TIMER
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

yahal::mcu::targets::msp430f5309::TimerA1::Comparator& \
yahal::mcu::targets::msp430f5309::TimerA1::comparator(unsigned int module)
{
	assert(module <= 2);

	switch (module) {
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

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr::setMode(OutputCompare::Mode::Type mode)
{
	switch(mode)
	{
	case OutputCompare::Mode::OFF:
		return setMode(Ccr::Mode::OC_OFF);

	case OutputCompare::Mode::SET:
		return setMode(Ccr::Mode::OC_SET);

	case OutputCompare::Mode::RESET:
		return setMode(Ccr::Mode::OC_RESET);

	case OutputCompare::Mode::SET_RESET:
		return setMode(Ccr::Mode::OC_SET_RESET);

	case OutputCompare::Mode::RESET_SET:
		return setMode(Ccr::Mode::OC_RESET_SET);

	case OutputCompare::Mode::TOGGLE:
		return setMode(Ccr::Mode::OC_TOGGLE);

	case OutputCompare::Mode::TOGGLE_SET:
		return setMode(Ccr::Mode::OC_TOGGLE_SET);

	case OutputCompare::Mode::TOGGLE_RESET:
		return setMode(Ccr::Mode::OC_TOGGLE_RESET);

	default:
		return false;
	}

}


bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr::writeCctlMode(volatile uint16_t& cctl,
								   Mode::Type mode)
{
	uint16_t config = cctl;
	config &= ~(OUTMOD0 + OUTMOD1 + OUTMOD2 + CCIE);

	switch(mode)
	{
	case Mode::OC_OFF:
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
		break;
	case Mode::IC_OFF: //TODO!!!!
		break;
	default:
		return false;
	}

	config |= CCIE;	// Enable IRQ
	cctl = config;	// Write configuration
	return true;
}


/* =================================================================================================
	TIMER A1 :: CCR0
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr0::setMode(Ccr::Mode::Type mode)
{
	return Ccr::writeCctlMode(TA1CCTL0, mode);
}


void yahal::mcu::targets::msp430f5309::TimerA1::Ccr0::setComparator(uint16_t value)
{
	TA1CCR0 = value;
}

uint16_t yahal::mcu::targets::msp430f5309::TimerA1::Ccr0::getComparator(void) const
{
	return TA1CCR0;
}

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr0::getOutput(void) const
{
	return TA1CCTL0 & CCI;
}




/* =================================================================================================
	TIMER A1 :: CCR1
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setMode(Ccr::Mode::Type mode)
{
	bool config_success = Ccr::writeCctlMode(TA1CCTL1, mode);

	if(mode == Mode::OC_OFF || not config_success)
	{
		/// DISCONNECT GPIO (input & GPIO mode)
		P2DIR &= ~1;
		P2SEL &= ~1;
	}
	else
	{
		/// ENABLE GPIO
		P2SEL |= 1;
		P2DIR |= 1;
	}

	return config_success;
}

void yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setComparator(uint16_t value)
{
	TA1CCR1 = value;
}

uint16_t yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::getComparator(void) const
{
	return TA1CCR1;
}

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::getOutput(void) const
{
	return TA1CCTL1 & CCI;
}






/* =================================================================================================
	TIMER A1 :: CCR2
================================================================================================= */

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setMode(Ccr::Mode::Type mode)
{
	return Ccr::writeCctlMode(TA1CCTL2, mode);
}

void yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setComparator(uint16_t value)
{
	TA1CCR2 = value;
}

uint16_t yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::getComparator(void) const
{
	return TA1CCR2;
}

bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::getOutput(void) const
{
	return TA1CCTL2 & CCI;
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
