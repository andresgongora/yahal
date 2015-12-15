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





#ifndef __YAHAL_MCU_IRQ_HPP_INCLUDED__
#define __YAHAL_MCU_IRQ_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include "../base_module.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	class Irq;
}



/* ============================================================================================== */
 *	yahal::mcu::Irq
 ** WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class yahal::mcu::Irq : public yahal::mcu::BaseModule
{
public:
				// CONSTRUCTOR & DESTRUCTOR
				Irq(void)	{}
	virtual			~Irq(void)	{}


				// INITIALIZATION
//	virtual bool		init(void) = 0;


				// CONFIGURATION
//	virtual void		enableGlobalInterrupts(void) const = 0;
//	virtual void		disableGlobalInterrupts(void) const = 0;



		struct I2C {enum type {
			TX_BUFFER_EMPTY,
			RX_BUFFER_FULL,
			RECEIVED_NACK,
			RECEIVED_START,
		};};


		struct UART {enum type {
			RX,
			TX,
		};};

		struct GPIO {enum type {
			A,
			B
		};};




		struct ERROR {enum type {
			NONE = 0,
			OTHER
		};};
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_IRQ_HPP_INCLUDED__
