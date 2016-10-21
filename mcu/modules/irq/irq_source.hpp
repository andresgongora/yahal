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


#ifndef __YAHAL_MCU_MODULES_IRQ_SOURCE_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_IRQ_SOURCE_HPP_INCLUDED__


#include <stdint.h>
#include "../modules_namespace.hpp"
#include "irq_handler.hpp"




/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
template<typename T_IRQ>
class yahal::mcu::modules::IrqSource
{
public:
				IrqSource(yahal::mcu::modules::IrqHandler& handler) :
					p_handler_(handler)	{}

				IrqSource(void) :
					p_handler_(NULL)	{}

protected:
	void			setHandler(yahal::mcu::modules::IrqHandler& handler)
				{
					p_handler_ = handler;
				}


	void			throwIrq(T_IRQ irq)
				{
					if(handler) { p_handler_->isr(irq); }
				}


private:
	yahal::mcu::modules::IrqHandler<T_IRQ>*	p_handler_;

};




/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_IRQ_SOURCE_HPP_INCLUDED__
