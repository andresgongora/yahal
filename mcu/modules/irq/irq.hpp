// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|										|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/


#ifndef __MCU_IRQ_HPP_INCLUDED__
#define __MCU_IRQ_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../generic_module.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{
	class Irq;
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::Irq
 ** WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::Irq : public mcu::GenericModule
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



/** ============================================================================================ **/
#endif 	//__MCU_IRQ_HPP_INCLUDED__
