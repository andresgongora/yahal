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

#ifndef __YAHAL_MCU_MSP430F5309_TIMER_A1_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_TIMER_A1_HPP_INCLUDED__


#include "../../../config/targets/msp430f5309.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1


#include <stdint.h>
#include <cstddef>
#include "../../../modules/timer/timer.hpp"
#include "../../../../utility/oop/publish_subscribe.hpp"
#include "../../../../utility/oop/singleton.hpp"
#include "../irq/timer_a1.hpp"



/***********************************************************************************************//**
 * @brief
 *
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA1 :
	public yahal::mcu::modules::Timer16,
	private yahal::mcu::targets::msp430f5309::irq::TimerA1
{
public:
				struct ClockSource{ enum Type{
					TA1CLK 		= 0x0000,
					ACLK		= 0x0100,
					SMCLK		= 0x0200,
					INCLK		= 0x0300
				};}static const CLOCK_SOURCE;


				struct Prescaler{ enum Type{
					DIVIDER_1	= 0x0000,
					DIVIDER_2	= 0x0040,
					DIVIDER_4	= 0x0080,
					DIVIDER_8	= 0x00C0
				};}static const PRESCALER;


				struct Mode{ enum Type{
					OFF		= 0x0000,
					UP_CCR0 	= 0x0010,
					CONTINUOUS	= 0x0020,
					UP_CCR0_DOWN	= 0x0030
				};}static const MODE;


				struct Event{ enum Type{
					TIMER 		= -1,
					CCR0		=  0,
					CCR1		=  1,
					CCR2		=  2
				};}static const EVENT;


				// -----------------------------------------------------------------
public:
				class Ccr  : public Comparator
				{
					friend class TimerA1;
				public:
					struct Mode{ enum Type{
						OC_OFF,
						OC_SET,
						OC_TOGGLE_RESET,
						OC_SET_RESET,
						OC_TOGGLE,
						OC_RESET,
						OC_TOGGLE_SET,
						OC_RESET_SET,

						IC_OFF,
					};}static const MODE;

				public:
					virtual bool	setMode(Mode::Type) = 0;


					virtual bool	setMode(OutputCompare::Mode::Type mode);

					class Empty;
				protected:
					bool	writeCctlMode(volatile uint16_t& cctl,
							      Mode::Type mode);
				};

				// -----------------------------------------------------------------
private:
				class Ccr0 : public Ccr
				{
				public:
					virtual bool		setMode(Ccr::Mode::Type mode);
					virtual void		setComparator(uint16_t value);
					virtual uint16_t	getComparator(void) const;
					virtual bool		getOutput(void) const;
				};

				class Ccr1 : public Ccr
				{
				public:
					virtual bool		setMode(Ccr::Mode::Type mode);
					virtual void		setComparator(uint16_t value);
					virtual uint16_t	getComparator(void) const;
					virtual bool		getOutput(void) const;
				};

				class Ccr2 : public Ccr
				{
				public:
					virtual bool		setMode(Ccr::Mode::Type mode);
					virtual void		setComparator(uint16_t value);
					virtual uint16_t	getComparator(void) const;
					virtual bool		getOutput(void) const;
				};

				// -----------------------------------------------------------------
public:
				TimerA1(void);

	void			configure(ClockSource::Type clock_source,
					  Prescaler::Type prescaler,
					  Mode::Type mode);

	virtual void		setCount(uint16_t count);
	virtual uint16_t	getCount(void) const;
//	virtual void		reset(void);
	virtual Comparator&	comparator(unsigned int module);


private:
	virtual void		isr(int);


private:
	Ccr0			ccr0_;
	Ccr1			ccr1_;
	Ccr2			ccr2_;
};



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA1::Ccr::Empty :
	public yahal::mcu::targets::msp430f5309::TimerA1::Ccr,
	public yahal::utility::oop::Singleton<Empty>
{
public:
	virtual bool		setMode(Mode::Type mode)	{return false;}
	virtual void		setComparator(uint16_t value)	{}
	virtual uint16_t	getComparator(void) const	{return 0;}
	virtual bool		getOutput(void)	const		{return 0;}
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
#endif // __YAHAL_MCU_MSP430F5309_TIMER_A1_HPP_INCLUDED__
