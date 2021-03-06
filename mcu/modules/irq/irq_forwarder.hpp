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


#ifndef __YAHAL_MCU_MODULES_IRQ_FORWARDER_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_IRQ_FORWARDER_HPP_INCLUDED__


#include "../modules_namespace.hpp"
#include "isr_handler.hpp"
#include "isr_source.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
template<typename T_IRQ>
class yahal::mcu::modules::IrqForwarder :
	public yahal::mcu::modules::IrqSource<T_IRQ>,
	public yahal::mcu::modules::IrqHandler<T_IRQ>
{
private:
	friend class		yahal::mcu::modules::IrqSource<T_IRQ>;
	virtual void		isr(T_IRQ irq)	{ throwIrq(irq); }
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_IRQ_FORWARDER_HPP_INCLUDED__
