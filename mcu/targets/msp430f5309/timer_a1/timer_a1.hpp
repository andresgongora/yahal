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



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../config/targets/msp430f5309/config.hpp"
#if YAHAL_MCU_MSP430F5309_TIMER_A1_ENABLED == true

#include <stdint.h>
#include <cstddef>
#include "../../../modules/timer/timer_16.hpp"
//#include "../../../modules/output_compare/output_compare.hpp"
#include "../../../../utility/oop/publish_subscribe.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class TimerA1;
	class IrqHandler;	//Forward declaration
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA1 : public yahal::mcu::modules::Timer16
{
public:
				struct ClockSource{ enum Type{
					TA1CLK 	= 0,
					ACLK	= 1,
					SMCLK	= 2,
					INCLK	= 3
				};}static const CLOCK_SOURCE;


				struct Mode{ enum Type{
					STOP		= 0,
					UP_CCR0 	= 1,
					CONTINUOUS	= 2,
					UP_DOWN		= 3,
				};}static const MODE;


				struct Divider{ enum Type{
					DIVIDER_1	= 0,
					DIVIDER_2	= 1,
					DIVIDER_4	= 2,
					DIVIDER_8	= 3,
				};}static const DIVIDER;


				struct Configuration
				{
					ClockSource::Type clock_source;
					Divider::Type divider;
					Mode::Type mode;
				};


				struct Event { enum Type {
					OVERFLOW= Timer16::Event::OVERFLOW,
					PERIOD	= Timer16::Event::PERIOD,
					CCR1	= 1,
					CCR2	= 2
				};};


private:
				struct Irq { enum Type {
					TIMER,
					CCR1,
					CCR2
				};};

				// -----------------------------------------------------------------
public:
				class Ccr  :
					public yahal::mcu::modules::Timer16::OutputCompare,
					public yahal::mcu::modules::Timer16::InputCapture
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
	virtual void		setCount(uint16_t count);
	virtual uint16_t	getCount(void) const;
	virtual void		setPeriod(uint16_t period);
	virtual void		reset(void);

				// -----------------------------------------------------------------
public:
				static TimerA1&		getInstance(void);
				bool			init(void);

				Ccr&			ccr(std::size_t module);

private:
				TimerA1(const Configuration& configuration);	///< Singleton

	friend class		yahal::mcu::targets::msp430f5309::IrqHandler;
	void			isrCcr0(void);
	void			isr(Irq::Type);

	static TimerA1		instance_;
	const Configuration&	configuration_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_TIMER_A1_ENABLED == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_MSP430F5309_TIMER_A1_HPP_INCLUDED__
