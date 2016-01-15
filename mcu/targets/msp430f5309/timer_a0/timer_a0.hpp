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

#include <stdint.h>
#include <cstddef>
#include "../../../modules/timer/timer.hpp"
#include "../../../modules/output_compare/output_compare.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class TimerA0;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::TimerA0 :
	public yahal::mcu::modules::Timer
{
public:
				struct ClockSource{ enum Type{
					VLP,
				};};


				struct Configuration
				{
					ClockSource::Type clockSource;
				};


				class Ccr :
					public yahal::mcu::modules::OutputCompare
				{
				public:
				protected:
				private:
// DEBERIA QUITAR BASE MODULE DE TODAS PARTES?????????					virtual void doInit(){}
				};


				// CONSTRUCTOR
				TimerA0(const Configuration& configuration);

	Ccr&			ccr(std::size_t module);



private:			// INITIALIZATION
	virtual void		doInit(void);





private:
				class Ccr1 : public Ccr
				{
				public:

				};

				class Ccr2 : public Ccr
				{
				public:

				};

				class Ccr3 : public Ccr
				{
				public:

				};

				class Ccr4 : public Ccr
				{
				public:

				};

				class Ccr5 : public Ccr
				{
				public:

				};

				class Ccr6 : public Ccr
				{
				public:

				};



				// PRIVATE VARIABLES
	const Configuration&	configuration_;
	Ccr1			ccr1_;
	Ccr2			ccr2_;
	Ccr3			ccr3_;
	Ccr4			ccr4_;
	Ccr5			ccr5_;
	Ccr6			ccr6_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_MSP430F5309_TIMER_A0_HPP_INCLUDED__
