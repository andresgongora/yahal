// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
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


#ifndef __MCU_RTOS_API_MUTEX_HPP_INCLUDED__
#define __MCU_RTOS_API_MUTEX_HPP_INCLUDED__


/** ---- INCLUDE ------------------------------------------------------------------------------- **/



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace rtos{ namespace api{
	class Mutex;
}}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::rtos::api::Mutex
{
public:
				// CONSTRUTOR & DESTRUCTOR
				Mutex(void)	{}
	virtual			~Mutex(void)	{}


				// Mutex
	virtual void		lock(void) = 0;
	virtual bool		try_lock(void) = 0;
	virtual void		unlock(void) = 0;
};



/** ============================================================================================ **/
#endif	// __MCU_RTOS_API_MUTEX_HPP_INCLUDED__
