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
#include <msp430f5309.h>


/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA1 :
	public yahal::mcu::modules::Timer16
{
public:
				struct Event{ enum Type{
					TIMER 		= -1,
					CCR0		=  0,
					CCR1		=  1,
					CCR2		=  2
				};};


private:
				struct ClockSource{ enum Type{
					TA1CLK 		= 0x0000,
					ACLK		= 0x0100,
					SMCLK		= 0x0200,
					INCLK		= 0x0300
				};};

				struct Prescaler{ enum Type{
					DIVIDER_1	= 0x0000,
					DIVIDER_2	= 0x0040,
					DIVIDER_4	= 0x0080,
					DIVIDER_8	= 0x00C0
				};};

				struct Mode{ enum Type{
					OFF		= 0x0000,
					UP_CCR0 	= 0x0010,
					CONTINUOUS	= 0x0020,
					UP_CCR0_DOWN	= 0x0030
				};};

				struct Irq{ enum Type{
					TIMER,
					CCR0,
					CCR1,
					CCR2
				};};

				struct CcrMode
				{
					struct OC{ enum Type{
						NONE,
						SET,
						RESET,
						SET_RESET,
						RESET_SET,
						TOGGLE,
						TOGGLE_SET,
						TOGGLE_RESET
					};};

					struct IC{ enum Type{
						NONE
					};};
				};


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

				// -----------------------------------------------------------------

				template<volatile uint16_t& T_CCR,
					 volatile uint16_t& T_CCTL>
				class Ccr  : public Comparator
				{
					friend class TimerA1;

					class Configuration
					{
						class Mode
						{
							class OutputCompare
							{
								void set() {
									configure(CcrMode::OC::SET);
								}
								void reset()	{
									configure(CcrMode::OC::RESET);
								}
								void setReset() {
									configure(CcrMode::OC::SET_RESET);
								}
								void resetSet() {
									configure(CcrMode::OC::RESET_SET);
								}
								void toggle() {
									configure(CcrMode::OC::TOGGLE);
								}
								void toggleSet() {
									configure(CcrMode::OC::TOGGLE_SET);
								}
								void toggleReset() {
									configure(CcrMode::OC::TOGGLE_RESET);
								}
							};

							class InputCapture
							{

							};

						public:
							OutputCompare	outputCompare;
							InputCapture	inputCapture;
						};
					public:
						Mode 	mode;
					};


				public:
					void	configure(CcrMode::OC::Type mode) {

						switch(mode)
						{
						default:	break;
						}

					}

					void	configure(CcrMode::IC::Type mode)
					{
						switch(mode)
						{
						default:	break;
						}
					}

					virtual void		set(uint16_t value) {
									T_CCR = value;
								}

					virtual uint16_t	get(void) const {
									return T_CCR;
								}
				};

				typedef Ccr<TA1CCR0,TA1CCTL0>	Ccr0;
				typedef Ccr<TA1CCR1,TA1CCTL1>	Ccr1;
				typedef Ccr<TA1CCR2,TA1CCTL2>	Ccr2;


				// -----------------------------------------------------------------
private:
				TimerA1(void);
				friend class yahal::mcu::targets::msp430f5309::Msp430f5309;

	virtual Comparator&	comparator(int ccr);

public:
	virtual void		setCount(uint16_t count);
	virtual uint16_t	getCount(void) const;

	Configuration		config;
	Ccr0			ccr0;
	Ccr1			ccr1;
	Ccr2			ccr2;

private:
	void			configure(ClockSource::Type);
	void			configure(Prescaler::Type);
	void			configure(Mode::Type);

	virtual void		isr(int);
	static void		TIMER1_A1_ISR(void);	///< TIMER_A1 IRQ for Overflow, CCR1 & CCR2
	static void		TIMER1_A0_ISR(void);	///< TIMER_A1 IRQ for CCR0
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
#endif // __YAHAL_MCU_MSP430F5309_TIMER_A1_HPP_INCLUDED__
