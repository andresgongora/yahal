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

#ifndef __YAHAL_MCU_MSP430F5309_ADC_10_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_ADC_10_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../config/targets/msp430f5309/config.hpp"
#if YAHAL_MCU_MSP430F5309_ADC_10_INSTANTIATE == true

#include <stdint.h>
#include <cstddef>




/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class Adc10;
	class IrqHandler;	//Forward declaration
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Adc10
{
public:
				struct ClockSource{ enum Type{
					TA1CLK 	= 0,
					ACLK	= 1,
					SMCLK	= 2,
					INCLK	= 3
				};};


				struct Mode{ enum Type{
					STOP		= 0,
					UP_CCR0 	= 1,
					CONTINUOUS	= 2,
					UP_DOWN		= 3,
				};};


				struct Divider{ enum Type{
					DIVIDER_1	= 0,
					DIVIDER_2	= 1,
					DIVIDER_4	= 2,
					DIVIDER_8	= 3,
				};};


				struct Configuration
				{
				};

private:
				struct Irq { enum Type {
				};};

				// -----------------------------------------------------------------


				// -----------------------------------------------------------------
public:


				// -----------------------------------------------------------------
public:
				static Adc10&		getInstance(void);
				bool			init(void);


private:
				Adc10(const Configuration& configuration);	///< Singleton

	friend class		yahal::mcu::targets::msp430f5309::IrqHandler;
	void			isr(Irq::Type);

	static Adc10		instance_;
	const Configuration&	configuration_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ADC_10_INSTANTIATE == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_MSP430F5309_ADC_10_HPP_INCLUDED__
