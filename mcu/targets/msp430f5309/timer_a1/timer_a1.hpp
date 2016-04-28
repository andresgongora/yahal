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
#include "../msp430f5309_namespace.hpp"
#include "../../../../cool/src/pattern/creational/singleton.hpp"
#include "../../../../utility/oop/publish_subscribe.hpp"


/***********************************************************************************************//**
 * @brief
 *
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA1 :
	public yahal::mcu::modules::Timer16,
	public cool::pattern::creational::Singleton<TimerA1>
{
public:
				struct Event{ enum Type{
					TIMER 		= -1,
					CCR0		=  0,
					CCR1		=  1,
					CCR2		=  2
				};}static const EVENT;

				//------------------------------------------------------------------
private:
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


				struct Irq{ enum Type{
					TIMER,
					CCR0,
					CCR1,
					CCR2
				};} static const IRQ;


				// -----------------------------------------------------------------
private:
				class Configuration
				{
					class ClockSource
					{
					public:
						void ta1clk();
						void aclk();
						void smclk();
						void inclk();
					};

					class Prescaler
					{
					public:
						void divideBy1();
						void divideBy2();
						void divideBy4();
						void divideBy8();
					};

					class Mode
					{
					public:
						void off();
						void upCcr0();
						void continuos();
						void upCcr0Down();
					};


				public:
					ClockSource 	clockSource;
					Prescaler	prescaler;
					Mode		mode;
				};

				class Ccr  : public Comparator
				{
					friend class TimerA1;

				public:
					struct Mode
					{
						enum Type{
							OFF,
							OUTPUT_COMPARE,
							INPUT_CAPTURE,
						};

						struct OutputCompare{ enum Type{
							NONE,
							SET,
							RESET,
							SET_RESET,
							RESET_SET,
							TOGGLE,
							TOGGLE_SET,
							TOGGLE_RESET
						};} static const OC;

						struct InputCapture{ enum Type{
							NONE
						};} static const IC;
					} static const MODE;

				public:
				//	using Comparator::setMode;

				//	bool	setMode(Ccr::Mode::Type);
				//	bool	setMode(Ccr::Mode::OutputCompare::Type mode);
				//	bool	setMode(Ccr::Mode::InputCapture::Type mode);

					class	Empty;
				protected:
					bool	writeCctlMode(volatile uint16_t& cctl,
							      Mode::Type mode);
				};

				// -----------------------------------------------------------------
private:
				class Ccr0 : public Ccr
				{
				public:
				//	virtual bool	setMode(Comparator::Mode::Type);
				//	virtual bool	setMode(Comparator::Mode::OutputCompare::Type);
				//	virtual bool	setMode(Comparator::Mode::InputCapture::Type);

					virtual void		setComparator(uint16_t value);
					virtual uint16_t	getComparator(void) const;
					virtual bool		getOutput(void) const;
				};

				class Ccr1 : public Ccr
				{
				public:
				//	virtual bool	setMode(Comparator::Mode::Type);
				//	virtual bool	setMode(Comparator::Mode::OutputCompare::Type);
				//	virtual bool	setMode(Comparator::Mode::InputCapture::Type);

					virtual void		setComparator(uint16_t value);
					virtual uint16_t	getComparator(void) const;
					virtual bool		getOutput(void) const;
				};

				class Ccr2 : public Ccr
				{
				public:
				//	virtual bool	setMode(Comparator::Mode::Type);
				//	virtual bool	setMode(Comparator::Mode::OutputCompare::Type);
				//	virtual bool	setMode(Comparator::Mode::InputCapture::Type);

					virtual void		setComparator(uint16_t value);
					virtual uint16_t	getComparator(void) const;
					virtual bool		getOutput(void) const;
				};

				// -----------------------------------------------------------------
private:
				// SINGLETON
				TimerA1(void);
	friend class		TimerA1::Singleton;


private:
	void			config(ClockSource::Type);
	void			config(Prescaler::Type);
	void			config(Mode::Type);

public:
	virtual void		setCount(uint16_t count);
	virtual uint16_t	getCount(void) const;
//	virtual void		reset(void);


	virtual Ccr&		comparator(int ccr);


private:
	virtual void		isr(int);
	static void		TIMER1_A1_ISR(void);	///< TIMER_A1 IRQ for Overflow, CCR1 & CCR2
	static void		TIMER1_A0_ISR(void);	///< TIMER_A1 IRQ for CCR0


public:
	Configuration		config;

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
	public cool::pattern::creational::Singleton<Ccr::Empty>
{
//	using Ccr::setMode;
public:
//	virtual bool		setMode(Comparator::Mode::Type)			{return false;}
//	virtual bool		setMode(Comparator::Mode::OutputCompare::Type)	{return false;}
//	virtual bool		setMode(Comparator::Mode::InputCapture::Type)	{return false;}

	virtual void		setComparator(uint16_t value)	{}
	virtual uint16_t	getComparator(void) const	{return 0;}
	virtual bool		getOutput(void)	const		{return 0;}
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
#endif // __YAHAL_MCU_MSP430F5309_TIMER_A1_HPP_INCLUDED__
