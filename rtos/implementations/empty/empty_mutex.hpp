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

#ifndef __YAHAL_RTOS_EMPTY_MUTEX_HPP_INCLUDED__
#define __YAHAL_RTOS_EMPTY_MUTEX_HPP_INCLUDED__


/** ---- INCLUDE ------------------------------------------------------------------------------- **/
#include "empty.hpp"
#if MCU_RTOS == MCU_RTOS_EMPTY

#include "../../api/api_mutex.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{namespace rtos{
	class Mutex;
}}



/***********************************************************************************************//**
 * @brief	Does absolutely nothing.
 **************************************************************************************************/
class yahal::rtos::Mutex : public yahal::rtos::api::Mutex
{
public:
				// CONSTRUTOR & DESTRUCTOR
				Mutex(void) : _locked(false)	{}


				// Mutex
	void			lock(void)	{}
	bool			try_lock(void) 	{return true}
	void			unlock(void)	{}
};



/* ---------------------------------------------------------------------------------------------- */
#endif	// MCU_RTOS == MCU_RTOS_EMPTY
#endif	// __YAHAL_RTOS_EMPTY_MUTEX_HPP_INCLUDED__
