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
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309
#if YAHAL_MCU_MSP430F5309_TIMER_A1_INSTANTIATE == true

#include <msp430f5309.h>
#include "../../../config/targets/msp430f5309/timer_a1.hpp"
#include "../../../../error/assert.hpp"



/* =================================================================================================
	TIMER A1
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA1	\
yahal::mcu::targets::msp430f5309::TimerA1::instance_(yahal::mcu::targets::msp430f5309::config::timer_a1);


yahal::mcu::targets::msp430f5309::TimerA1&
yahal::mcu::targets::msp430f5309::TimerA1::getInstance(void)
{
	return instance_;
}

/* ---------------------------------------------------------------------------------------------- */


yahal::mcu::targets::msp430f5309::TimerA1::TimerA1(const Configuration& configuration) :
	configuration_(configuration)
{}




bool yahal::mcu::targets::msp430f5309::TimerA1::init(void)
{
	uint16_t conf = 0;

	conf |= (configuration_.clock_source << 8);	///< Select clock source
	conf |= (configuration_.divider << 6);		///< Select clock divider
	conf |= (configuration_.mode << 4);		///< Select mode
	conf |= TAIE;					///< Enable IRQ

	TA1CTL = conf;

	return true;
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
	switch (module) {
	case 1:
		return Ccr1::getInstance();
	case 2:
		return Ccr2::getInstance();
	default:
		assert(false);
		return Ccr1::getInstance();;	///< TODO: Better return this than nothing.
	}
}


void yahal::mcu::targets::msp430f5309::TimerA1::isrCcr0(void)
{
	this->publish(Event::PERIOD);
}


void yahal::mcu::targets::msp430f5309::TimerA1::isr(Irq::Type irq)
{
	switch (irq) {
	case Irq::TIMER:
		publish(Event::OVERFLOW);
		break;
	case Irq::CCR1:
		publish(1); //TODO
		break;
	case Irq::CCR2:
		publish(2); //TODO
		break;
	default:
		break;
	}
}




/* =================================================================================================
	TIMER A1 CCR1
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA1::Ccr1	\
yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::instance_;


yahal::mcu::targets::msp430f5309::TimerA1::Ccr1&
yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::getInstance(void)
{
	return instance_;
}


yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::Ccr1(void)
{}

/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setOutput(bool b)
{
	b ? TA1CCTL1 |= 0x0001 : TA1CCTL1 &= ~0x0001;
}


bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::getOutput(void)
{
	return TA1CCTL1 & 0x0001;
}


void yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setMode(Mode::Type mode)
{
	uint16_t aux = TA1CCTL1;
	aux &= 0xFF1F;
	aux |= (mode << 5);
	TA1CCTL1 = aux;

	//TODO: No me gusta esto aqui: controla el puerto 2.0
	P2DIR |= 1;
	P2SEL |= 1;
}


void yahal::mcu::targets::msp430f5309::TimerA1::Ccr1::setComparator(uint16_t value)
{
	TA1CCR1 = value;
}



/* =================================================================================================
	TIMER A1 CCR2
================================================================================================= */

yahal::mcu::targets::msp430f5309::TimerA1::Ccr2	\
yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::instance_;


yahal::mcu::targets::msp430f5309::TimerA1::Ccr2&
yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::getInstance(void)
{
	return instance_;
}


yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::Ccr2(void)
{}

/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setOutput(bool b)
{
	b ? TA1CCTL2 |= 0x0001 : TA1CCTL2 &= ~0x0001;
}


bool yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::getOutput(void)
{
	return TA1CCTL2 & 0x0001;
}


void yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setMode(Mode::Type mode)
{
	uint16_t aux = TA1CCTL2;
	aux &= 0xFF1F;
	aux |= (mode << 5);
	TA1CCTL2 = aux;
}


void yahal::mcu::targets::msp430f5309::TimerA1::Ccr2::setComparator(uint16_t value)
{
	TA1CCR2 = value;
}




/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_TIMER_A1_INSTANTIATE == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
