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

#ifndef __YAHAL_MCU_MSP430F5309_TIMER_A0_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_TIMER_A0_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../config/targets/msp430f5309/config.hpp"
#if YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true

#include <stdint.h>
#include <cstddef>
//#include "../../../modules/timer/timer.hpp"
//#include "../../../modules/output_compare/output_compare.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class TimerA0;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA0
{
public:
				struct ClockSource{ enum Type{
					VLP,
				};};


				struct Mode{ enum Type{
					STOP		= 0,
					UP_CCR0 	= 1,
					CONTINUOUS	= 2,
					UP_DOWN		= 3,
				};};


				struct Configuration
				{
					ClockSource::Type clock_source;
					bool	ccr0_output_enable;
					bool	ccr1_output_enable;
					bool	ccr2_output_enable;
					bool	ccr3_output_enable;
					bool	ccr4_output_enable;
				};

				struct Irq { enum Type {
				};};


				class OutputCompare
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
						RESET_SET	= 7
					};};

					virtual void setOutput(bool b) = 0;
					virtual bool getOutput(void) = 0;
					virtual void setMode(Mode::Type mode) = 0;
				};

				class Ccr :
					public OutputCompare
				{

				};

				// -----------------------------------------------------------------
private:
				class Ccr0 : public Ccr
				{
				public:
					static Ccr0&	getInstance(void);
					virtual void	setOutput(bool b);
					virtual bool	getOutput(void);
					virtual void	setMode(Mode::Type mode);

				private:
							Ccr0(void);	///< Singleton
					static Ccr0 	instance_;
				};

				class Ccr1 : public Ccr
				{
				public:
					static Ccr1&	getInstance(void);
					virtual void	setOutput(bool b);
					virtual bool	getOutput(void);
					virtual void	setMode(Mode::Type mode);

				private:
							Ccr1(void);	///< Singleton
					static Ccr1 	instance_;
				};

				class Ccr2 : public Ccr
				{
				public:
					static Ccr2&	getInstance(void);
					virtual void	setOutput(bool b);
					virtual bool	getOutput(void);
					virtual void	setMode(Mode::Type mode);

				private:
							Ccr2(void);	///< Singleton
					static Ccr2 	instance_;
				};

				class Ccr3 : public Ccr
				{
				public:
					static Ccr3&	getInstance(void);
					virtual void	setOutput(bool b);
					virtual bool	getOutput(void);
					virtual void	setMode(Mode::Type mode);

				private:
							Ccr3(void);	///< Singleton
					static Ccr3 	instance_;
				};

				class Ccr4 : public Ccr
				{
				public:
					static Ccr4&	getInstance(void);
					virtual void	setOutput(bool b);
					virtual bool	getOutput(void);
					virtual void	setMode(Mode::Type mode);

				private:
							Ccr4(void);	///< Singleton
					static Ccr4 	instance_;
				};

				// -----------------------------------------------------------------
public:
	static TimerA0&		getInstance(void);
	bool			init(void);

	Ccr&			ccr(std::size_t module);

	void			set(std::size_t value);
	std::size_t		get(void) const;
	void			reset(void) const;
	void			setMode(Mode::Type mode);


private:
				TimerA0(const Configuration& configuration);	///< Singleton

	static TimerA0		instance_;
	const Configuration&	configuration_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_TIMER_A0_INSTANTIATE == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_MSP430F5309_TIMER_A0_HPP_INCLUDED__
