// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------+-----------------------------------+
	|                                                                       |
	|             Yet Another Hardware Abstraction Layer (YAHAL)            |
	|                https://github.com/andresgongora/yahal                 |
	|                                                                       |
	|                                                                       |
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file. |
	| Machine Perception and Intelligent Robotics (MAPIR),                  |
	| University of Malaga. <http://mapir.isa.uma.es>                       |
	|                                                                       |
	| This program is free software: you can redistribute it and/or modify  |
	| it under the terms of the GNU General Public License as published by  |
	| the Free Software Foundation, either version 3 of the License, or     |
	| (at your option) any later version.                                   |
	|                                                                       |
	| This program is distributed in the hope that it will be useful,       |
	| but WITHOUT ANY WARRANTY; without even the implied warranty of        |
	| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
	| GNU General Public License for more details.                          |
	|                                                                       |
	| You should have received a copy of the GNU General Public License     |
	| along with this program. If not, see <http://www.gnu.org/licenses/>.  |
	|                                                                       |
	+-----------------------------------------------------------------------+ */


#ifndef __YAHAL_MCU_MSP430F5309_IRQ_HANDLER_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_IRQ_HANDLER_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/targets/msp430f5309.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_IRQ


#include "../../../modules/irq/irq_handler.hpp"
#include "../msp430f5309_namespace.hpp"
#include "../../../../utility/oop/service_locator.hpp"
#include <stdint.h>
#include <msp430f5309.h>


/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::IrqHandler :
	public yahal::mcu::modules::IrqHandler
{
public:
	virtual void		enableGlobalIrq(void);
	virtual void		disableGlobalIrq(void);



#ifdef YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED
		static void		USCI_B1_ISR(void);
#endif


};



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_MSP430F5309_ENABLE_IRQ
#endif 	// __YAHAL_MCU_MSP430F5309_IRQ_HANDLER_HPP_INCLUDED__

