// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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




#ifndef __MCU_RTOS_ST_MUTEX_HPP_INCLUDED__
#define __MCU_RTOS_ST_MUTEX_HPP_INCLUDED__


/** ---- INCLUDE ------------------------------------------------------------------------------- **/
#include "st.hpp"
#if MCU_RTOS == MCU_RTOS_SINGLE_THREAD

#include "../../api/api_mutex.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace rtos{
	class Mutex;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::rtos::Mutex : public mcu::rtos::api::Mutex
{
public:
				// CONSTRUTOR & DESTRUCTOR
				Mutex(void) : _locked(false)	{}


				// Mutex
	void			lock(void)	{if(not _locked) {_locked = true;}}
	bool			try_lock(void) 	{return not _locked;}
	void			unlock(void)	{_locked = false;}

private:
	bool			_locked;
};



/** ============================================================================================ **/
#endif	// MCU_RTOS == MCU_RTOS_SINGLE_THREAD
#endif	// __MCU_RTOS_ST_MUTEX_HPP_INCLUDED__