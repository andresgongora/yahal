// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file.	|
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


#ifndef __YAHAL_ERROR_DEBUG_ASSERT_HPP_INCLUDED__
#define __YAHAL_ERROR_DEBUG_ASSERT_HPP_INCLUDED__


#include <cstddef>



/***********************************************************************************************//**
 * 	If "__DEBUG" is defined and the assert condition fails, the execution is stalled
 *	in an endless loop.
 *
 *	It is highly recommended to set a breakpoint here.
 *
 * @param	condition	Must be true to pass assertion.
 * @param	text		Can store a message for convenience, default to null string.
 * @param	code		Can store an integer for convenience, default 0.
 **************************************************************************************************/
namespace yahal{ namespace error{ namespace details{
	static void debug_assert(bool condition, const char* text="", std::size_t code=0)
	{
#ifdef __DEBUG
		while(not condition)
		{
			volatile std::size_t i;
			for(i=code; i>text[0]; i--);	// Make sure text and code are used to tell the compiler not to ingore them
		}
#endif
	}
}}}



/***********************************************************************************************//**
 * 	Macro to use assert storing __FILE__ as assert description and __LINE__ as code.
 * 	If __DEBUG is defined, calls debug_assert function.
 * 	Else does nothing
 **************************************************************************************************/
#ifdef __DEBUG
#define DEBUG_ASSERT(condition)	yahal::error::details::debug_assert(condition, __FILE__, __LINE__)
#else
#define DEBUG_ASSERT(condition)	do{}while(0)
#endif


/* ---------------------------------------------------------------------------------------------- */
#endif 	 // __YAHAL_ERROR_DEBUG_ASSERT_HPP_INCLUDED__
