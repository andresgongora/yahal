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
#if MCU_DEVICE == MCU_MSP430F5309

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
				class I2C
				{
				protected:		I2C(void) {}
				public:
							struct IRQ { enum Type {
								START,
								STOP,
								TX_BUFFER_EMPTY,
								RX_BUFFER_FULL,
								ARBITRATION_LOST,
								NACK,
							};};
				protected:
					friend class	IRQHandler;
					virtual void	isr(IRQHandler::I2C::IRQ::Type irq) = 0;
				};




public:
				/// Constructor
				IRQHandler(void);


public:
				// IRQ Control
	virtual void		enableGlobalInterrupts(void) const;
	virtual void		disableGlobalInterrupts(void) const;



				// I2C
	void 			setISRHandlerI2C(I2C* p_handler);
	void 			irqI2C(I2C::IRQ::Type irq);



private:
				// POINTERS
	I2C*			p_i2c_;

};


/* ---------------------------------------------------------------------------------------------- */
#endif	// MCU_DEVICE == MCU_MSP430F5309
#endif 	// __YAHAL_MCU_M430F5309_IRQ_HANDLER_HPP_INCLUDED__
