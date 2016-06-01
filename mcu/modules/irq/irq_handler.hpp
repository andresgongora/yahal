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


#ifndef __YAHAL_MCU_MODULES_ISR_PROVIDER_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_ISR_PROVIDER_HPP_INCLUDED__


#include <stdint.h>
#include "../modules_namespace.hpp"
//#include "../../../cool/src/pattern/decoupling/service_locator.hpp"
#include "../../../error/debug_assert.hpp"







/***********************************************************************************************//**
 * @brief	Base class for all IRQ handlers.
 **************************************************************************************************/
/*template<typename T_DERIVED>
class yahal::mcu::modules::IrqHandler
{
public:
	//virtual void		enableGlobalIrq(void) = 0;
	//virtual void		disableGlobalIrq(void) = 0;



	//cool::pattern::decoupling::ServiceLocator<T_DERIVED> handler_;

				IrqHandler(void) {handler_ = static_cast<T_DERIVED*>(this);}

	static void		irq(uint8_t code)
				{
					DEBUG_ASSERT(handler_ != NULL);
					handler_->isr(code);
				}

	virtual void		isr(uint8_t code) {for(;;);}


	static T_DERIVED*	handler_;

};

template<typename T_DERIVED>
T_DERIVED* yahal::mcu::modules::IrqHandler<T_DERIVED>::handler_ = NULL;
*/


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_ISR_PROVIDER_HPP_INCLUDED__
