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

#ifndef __YAHAL_RTOS_API_MUTEX_HPP_INCLUDED__
#define __YAHAL_RTOS_API_MUTEX_HPP_INCLUDED__

/* ---------------------------------------------------------------------------------------------- */
#include "../../utility/oop/noncopyable.hpp"


/* ---------------------------------------------------------------------------------------------- */
namespace yahal{namespace rtos{ namespace api{
	class Mutex;
}}}



/***********************************************************************************************//**
 * @brief	Base class for all MUTEX
 **************************************************************************************************/
class yahal::rtos::api::Mutex : private yahal::utility::oop::NonCopyable
{
public:
				// Mutex
	virtual void		lock(void) = 0;
	virtual bool		try_lock(void) = 0;
	virtual void		unlock(void) = 0;
};



/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_RTOS_API_MUTEX_HPP_INCLUDED__
