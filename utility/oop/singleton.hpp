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


#ifndef __YAHAL_UTILITY_OOP_SINGLETON_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_SINGLETON_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "is_base_of.hpp"
#include "../../error/static_assert.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	template<typename T_DERIVED> class Singleton;
}}}



/***********************************************************************************************//**
 * @brief	Singleton base class
 *
 * @code
 * 	class myns::MyClass : public Singleton<myns::MyClass>
 * 	{
 * 	private:
 * 		MyClass(void) {}
 * 		...
 * 	public:
 * 		...
 * 	};
 * @endcode
 **************************************************************************************************/
template<typename T_DERIVED>
class yahal::utility::oop::Singleton
{
protected:
	// PRIVATE CONSTRUCTOR
	Singleton(void) {}	// This class can only be used as a base class

	// SINGLETON INSTANCE
	static Singleton<T_DERIVED> instance_;

public:
	// ACCESSOR
	/// Because we have no access to the private constructor of T_DERIVED, a
	/// Singleton<T_DERIVED> instance is used. This instance shares the same memory
	/// direction as the derived class, thus it can be casted to that class.
	/// To avoid that the compiler complains, it is first casted to void*
	/// @warning: This looks very dangerous to me.
	static inline T_DERIVED& getInstance(void)
	{
		return *static_cast<T_DERIVED*>( static_cast<void*>(&instance_) );
	}
};


// CREATE INSTANCE
template<typename T_DERIVED> yahal::utility::oop::Singleton<T_DERIVED> \
	yahal::utility::oop::Singleton<T_DERIVED>::instance_;


/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_SINGLETON_HPP_INCLUDED__
