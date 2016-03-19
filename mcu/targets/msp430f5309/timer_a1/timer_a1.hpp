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
#include "../irq/irq_handler.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA1 :
	public yahal::mcu::modules::Timer<uint16_t>,
	private yahal::mcu::targets::msp430f5309::IrqHandler::TimerA1
{
public:
				struct ClockSource{ enum Type{
					TA1CLK 	= 0x0000,
					ACLK	= 0x0100,
					SMCLK	= 0x0200,
					INCLK	= 0x0300
				};}static const CLOCK_SOURCE;


				struct Prescaler{ enum Type{
					DIVIDER_1	= 0x0000,
					DIVIDER_2	= 0x0040,
					DIVIDER_4	= 0x0080,
					DIVIDER_8	= 0x00C0
				};}static const PRESCALER;


				struct Mode{ enum Type{
					STOP		= 0x0000,
					UP_CCR0 	= 0x0010,
					CONTINUOUS	= 0x0020,
					UP_DOWN		= 0x0030
				};}static const MODE;


				struct Event { enum Type {
					OVERFLOW= Timer::Event::OVERFLOW,
					PERIOD	= Timer::Event::PERIOD,
					CCR1	= 1,
					CCR2	= 2
				};};

				// -----------------------------------------------------------------
public:
				class Ccr  :
					public yahal::mcu::modules::Timer<uint16_t>::OutputCompare,
					public yahal::mcu::modules::Timer<uint16_t>::InputCapture
				{
				public:
					struct Mode{ enum Type{
						OUTPUT		= 0,
						SET		= 1,
						TOGGLE_RESET	= 2,
						SET_RESET	= 3,
						TOGGLE		= 4,
						RESET		= 5,
						TOGGLE_SET	= 6,
						RESET_SET	= 7,
						OFF		= 0xFF
					};};

					virtual void	setOutput(bool b) = 0;
					virtual void	setMode(Mode::Type mode) = 0;
				};

				// -----------------------------------------------------------------
private:
				class Ccr1 : public Ccr
				{
				public:
					static Ccr1&	getInstance(void);
					virtual bool	getOutput(void);
					virtual void	setOutput(bool b);
					virtual void	setMode(Mode::Type mode);
					virtual void	setComparator(uint16_t value);

				private:
							Ccr1(void);	///< Singleton
					static Ccr1 	instance_;
				};

				class Ccr2 : public Ccr
				{
				public:
					static Ccr2&	getInstance(void);
					virtual bool	getOutput(void);
					virtual void	setOutput(bool b);
					virtual void	setMode(Mode::Type mode);
					virtual void	setComparator(uint16_t value);

				private:
							Ccr2(void);	///< Singleton
					static Ccr2 	instance_;
				};

				// -----------------------------------------------------------------
public:
				TimerA1(void);

	virtual void		setCount(uint16_t count);
	virtual uint16_t	getCount(void) const;
	virtual void		setPeriod(uint16_t period);
	virtual void		reset(void);

	virtual void		isr(uint8_t);

	Ccr&			ccr(std::size_t module);

	void			configure(ClockSource::Type clock_source,
					  Prescaler::Type prescaler,
					  Mode::Type mode);
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
#endif // __YAHAL_MCU_MSP430F5309_TIMER_A1_HPP_INCLUDED__
