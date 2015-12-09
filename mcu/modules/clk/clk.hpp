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


#ifndef __MCU_CLK_HPP_INCLUDED__
#define __MCU_CLK_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <stdint.h>
#include "../generic_module.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{
	class Clk;
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::Clk
 ** WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::Clk : public mcu::GenericModule
{
public:
				struct ERROR{ enum type{
					NONE = 0,
					FREQUENCY_NOT_AVAILABLE,
					OTHER
				};};


protected:			// CONSTRUCTOR & DESTRUCTOR ----------------------------------------
	virtual			~Clk(void){}


public:				// CONFIGURATION ---------------------------------------------------
	virtual bool		setFrequencyHz(uint32_t desiredFrequencyHz) = 0;
	virtual	uint32_t	getFrequencyHz(void) = 0;

//	virtual inline uint8_t	getFreqMHzPeripherals(void) = 0;


};



/** ============================================================================================ **/
#endif 	//__MCU_CLK_HPP_INCLUDED__
