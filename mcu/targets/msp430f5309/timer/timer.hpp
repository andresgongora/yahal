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

#ifndef __MCU_M430F5309_TIMER_HPP_INCLUDED__
#define __MCU_M430F5309_TIMER_HPP_INCLUDED__



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../msp430f5309.hpp"
#ifdef __MCU_MSP430F5309_TIMER_ENABLED__

#include <stdint.h>




/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace targets{ namespace msp430f5309{
	class TimerA;
}}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	GPIO
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/
class mcu::targets::msp430f5309::TimerA
{
public:




};



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace hal{namespace uc{namespace msp430f5309{
	extern mcu::targets::msp430f5309::TimerA timerA;
}}}



/** ============================================================================================ **/
#endif // __MCU_MSP430F5309_TIMER_ENABLED__
#endif // __MCU_MSP430F5309_TIMER_HPP_INCLUDED__
