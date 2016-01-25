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
	| You should have received a heap of the GNU General Public License	|
	| along with this program.  If not, see <http://www.gnu.org/licenses/>. |
	|									|
	+-----------------------------------------------------------------------+	*/



#ifndef __YAHAL_UTILITY_OOP_NONHEAPABLE_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_NONHEAPABLE_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include <cstddef>



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	class NonHeapable;
}}}



/***********************************************************************************************//**
 * Non Heapable base class.
 * Each class that inherits from this class can not be instantiated with new.
 * Also it can not be removed with delete.
 **************************************************************************************************/
class yahal::utility::oop::NonHeapable
{
protected:
				NonHeapable(void)			{}

private:
	inline static void*	operator new(std::size_t)		{return static_cast<void*>(NULL);}
	inline static void*	operator new(std::size_t,void*)		{return static_cast<void*>(NULL);}
	inline static void*	operator new[](std::size_t)		{return static_cast<void*>(NULL);}
	inline static void*	operator new[](std::size_t,void*)	{return static_cast<void*>(NULL);}
	inline static void 	operator delete(void*)			{}
	inline static void 	operator delete[](void*)		{}
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_NONHEAPABLE_HPP_INCLUDED__
