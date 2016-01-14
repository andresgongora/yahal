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

#include <stdint.h>
#include <cstddef>
#include "../../../modules/irq/irq_handler.hpp"
#include "../uscib1/uscib1.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class IrqHandler;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::IrqHandler :
	public yahal::mcu::modules::details::IrqHandler
{
public:
				/// Constructor
				IrqHandler(void);


public:
				// IRQ Control
	virtual void		enableGlobalInterrupts(void) const;
	virtual void		disableGlobalInterrupts(void) const;



				// I2C
	void 			setISRHandlerUsciB1(yahal::mcu::targets::msp430f5309::UsciB1* p_handler);
	void 			irqUsciB1(yahal::mcu::targets::msp430f5309::UsciB1::IRQ::Type irq);



private:
				// POINTERS
	yahal::mcu::targets::msp430f5309::UsciB1*			p_handler_uscib1_;
};


/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif 	// __YAHAL_MCU_M430F5309_IRQ_HANDLER_HPP_INCLUDED__
