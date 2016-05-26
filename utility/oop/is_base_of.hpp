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



#ifndef __YAHAL_UTILITY_OOP_IS_BASE_OF_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_IS_BASE_OF_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "is_base_of.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	template <typename T_BASE, typename T_DERIVED> struct is_base_of;
}}}



/***********************************************************************************************//**
 *	Check whether T_Derived is derived from T_Base.
 **************************************************************************************************/
template <typename T_BASE, typename T_DERIVED>
struct yahal::utility::oop::is_base_of
{
private:
    typedef char yes[1];
    typedef char no[2];

    static yes& test(T_BASE*);
    static no& test(...);

    static T_DERIVED* get(void);

public:
    static const bool value = sizeof(test(get())) == sizeof(yes);
};



/***********************************************************************************************//**
 *	Helper macro for yahal::utility::oop::is_base_of
 **************************************************************************************************/
#define IS_BASE_OF(Base, Derived) (yahal::utility::oop::is_base_of<Base,Derived>::value)



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_IS_BASE_OF_HPP_INCLUDED__
