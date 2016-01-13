// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015, Individual contributors, see AUTHORS file. 	|
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



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class IRQHandler;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::IRQHandler :
	public yahal::mcu::modules::details::IRQHandler
{
public:
				/// I2C IRQ Handler
				class UsciB1
				{
				protected:		UsciB1(void) {}
				public:
							struct IRQ { enum Type {
								I2C_START,
								I2C_STOP,
								I2C_TX_BUFFER_EMPTY,
								I2C_RX_BUFFER_FULL,
								I2C_ARBITRATION_LOST,
								I2C_NACK,
							};};
				protected:
					friend class	IRQHandler;
					virtual void	isr(IRQHandler::UsciB1::IRQ::Type irq) = 0;
				};




public:
				/// Constructor
				IRQHandler(void);


public:
				// IRQ Control
	virtual void		enableGlobalInterrupts(void) const;
	virtual void		disableGlobalInterrupts(void) const;



				// I2C
	void 			setISRHandlerUsciB1(UsciB1* p_handler);
	void 			irqUsciB1(UsciB1::IRQ::Type irq);



private:
				// POINTERS
	UsciB1*			p_handler_uscib1_;
};


/* ---------------------------------------------------------------------------------------------- */
#endif	// MCU_DEVICE == MCU_MSP430F5309
#endif 	// __YAHAL_MCU_M430F5309_IRQ_HANDLER_HPP_INCLUDED__
