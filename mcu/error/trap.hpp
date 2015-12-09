// 1 TAB = 8 SPACES //

      /**
	*	ID:	trap.hpp
	*   EDITED:	2015.05.15
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|	Example of use:								|
	*	|	error::TRAP("In FOO class", __LINE__, getErrorCode());			|
	*	|										|
	*	|	Expects:	- const char	description				|
	*	|			- long int	line where trap wass called		|
	*	|			- long int	error code				|
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


#ifndef __TRAP_HPP_INCLUDED
#define __TRAP_HPP_INCLUDED


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <stdint.h>


/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace error{


/** --- DEFINE --------------------------------------------------------------------------------- **/
#define __DEBUG



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/


void TRAP(const char* description, long int line, int errorCode)
{
	#ifdef __DEBUG
		if(errorCode)
		{
			for(;;);
		}
	#endif
}


/** ============================================================================================ **/
}	// namespace error
#endif 	//__TRAP_HPP_INCLUDED


