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



#ifndef __TRAP_HPP_INCLUDED
#define __TRAP_HPP_INCLUDED


/* ---------------------------------------------------------------------------------------------- */
#include <cstddef>
#include "../utility/macros/concatenate.hpp"


/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace error{
	void assert(bool condition, const char* file, std::size_t line)
	{
		if(condition)
		{
			for(;;);
		}
	}
}}


#ifdef __DEBUG
#define assert(condition)	yahal::error::assert(condition,CONCATENATE("ASSERT_FAILED_IN_FILE_",__FILE__),__LINE__);
#else
#define assert(condition)	do{}while(0);
#endif

/* ---------------------------------------------------------------------------------------------- */
#endif 	//__TRAP_HPP_INCLUDED
