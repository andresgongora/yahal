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




#ifndef __YAHAL_MCU_MSP430F5309_CLK_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_CLK_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../modules/clk/clk.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class Clk;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Clk : public yahal::mcu::modules::Clk
{
public:
				struct Frequency{enum Type{
					DCO_1MHz = 1000000,
					DCO_2MHz = 2000000,
					DCO_4MHz = 4000000,
					DCO_8MHz = 8000000,
					DCO_16MHz = 16000000,
					DCO_32MHz = 32000000
				};};

				struct ClockSource{ enum Type{
					VLP,
				};};

				struct Configuration
				{
					Frequency::Type	frequency;
					ClockSource::Type clockSource;
				};

				// -----------------------------------------------------------------

public:
	static Clk&		getInstance(void);	///< Get singleton instance
	bool			init(const Configuration& configuration);


private:
				Clk(void){}		///< Singleton

	bool			setFrequencyHz(uint32_t desiredFrequencyHz);
	uint32_t		getFrequencyHz(void);

	static Clk 		instance_;
};


/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_MSP430F5309_CLK_HPP_INCLUDED__
