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

#ifndef __YAHAL_MCU_M430F5309_IRQ_HANDLER_HPP_INCLUDED__
#define __YAHAL_MCU_M430F5309_IRQ_HANDLER_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../config/targets/msp430f5309_config.hpp"
#include "../../../modules/irq/irq_handler.hpp"
#include "../usci_b1/usci_b1.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class IrqHandler;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::IrqHandler : public yahal::mcu::modules::details::IrqHandler
{
public:
	static IrqHandler&	getInstance(void);

	virtual void		enableGlobalInterrupts(void);
	virtual void		disableGlobalInterrupts(void);



private:
				IrqHandler(void) {};		///< Singleton
	static IrqHandler	instance_;


	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_USCI_B1_INSTANTIATE == true
		static void		USCI_B1_ISR(void);
		static UsciB1&		handler_usci_b1_;
	#endif
};




/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif 	// __YAHAL_MCU_M430F5309_IRQ_HANDLER_HPP_INCLUDED__
