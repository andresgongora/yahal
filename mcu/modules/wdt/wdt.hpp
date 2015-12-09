// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*    AUTOR:	Andres Gongora
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


#ifndef __MCU_WDT_HPP_INCLUDED__
#define __MCU_WDT_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../generic_module.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{
	class Wdt;
}




/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION	mcu::Wdt
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::Wdt : public mcu::GenericModule
{
protected:			// CONSTRUCTOR & DESTRUCTOR ----------------------------------------
				Wdt(void) {}
	virtual			~Wdt(void){}


	virtual void		reset(void) = 0;
};



/** ============================================================================================ **/
#endif 	//__MCU_WDT_HPP_INCLUDED__
