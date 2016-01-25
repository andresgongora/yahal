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




#ifndef __CPP_STATIC_ASSERT_HPP_INCLUDED__
#define __CPP_STATIC_ASSERT_HPP_INCLUDED__


#include "../utility/macros/concatenate.hpp"


#ifndef __cpp_static_assert

/***********************************************************************************************//**
 *	Create array of size 1 if true, and of size -1 if false, which can not be compiled.
 **************************************************************************************************/
	#define static_assert(condition)\
		typedef int CONCATENATE(ASSERTMACRO, __LINE__)[(condition) ? 1 : -1]



/***********************************************************************************************//**
 *	Create array of size 1 if true, and of size -1 if false, which can not be compiled.
 *	message is ignored
 **************************************************************************************************/
//	#define static_assert(condition, message)	static_assert(condition)
#endif




/* ---------------------------------------------------------------------------------------------- */
#endif 	//__CPP_STATIC_ASSERT_HPP_INCLUDED__
