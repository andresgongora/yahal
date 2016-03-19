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
namespace yahal{ namespace utility{ namespace oop{
	template<typename T_DERIVED> class Singleton;
}}}



/***********************************************************************************************//**
 * @brief	Singleton base class
 * @warning	All derived classes must befriend with Singleton and use the default private constructor
 *
 * @code
 * 	class myns::MyClass : public Singleton<myns::MyClass>
 * 	{
 * 		friend class Singleton<myns::MyClass>;
 * 	private:
 * 		MyClass(void) {}
 *		...
 *	public:
 *		...
 * 	};
 * @endcode
 **************************************************************************************************/
template<typename T_DERIVED>
class yahal::utility::oop::Singleton
{
protected:
	// PROTECTED CONSTRUCTOR
	Singleton(void)	{}

private:
	// SINGLETON INSTANCE
	static T_DERIVED instance_;

public:
	// ACCESSOR
	static inline T_DERIVED& getInstance(void) { return instance_; }
};


// CREATE INSTANCE
template<typename T_DERIVED> T_DERIVED yahal::utility::oop::Singleton<T_DERIVED>::instance_;


/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_SINGLETON_HPP_INCLUDED__
