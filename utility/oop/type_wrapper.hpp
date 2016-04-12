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


#ifndef __YAHAL_UTILITY_OOP_TYPE_WRAPPER_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_TYPE_WRAPPER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	template<typename T> class TypeWrapper;
}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
template<typename T>
class yahal::utility::oop::TypeWrapper
{
public:
				// CONSTRUCTORS
				TypeWrapper(void) {}
	explicit		TypeWrapper(T value) :	value_(value) {}
	explicit		TypeWrapper(const TypeWrapper<T>& other) : value_(other.value_) {}



	operator const		T & () const				{ return value_; }
	operator		T & ()					{ return value_; }

	TypeWrapper<T>&		operator=(const TypeWrapper<T>& other)	{ value_ = other.value_;return *this;}

	bool			operator==(const TypeWrapper<T>& other)	{return value_ == other.value_;}
	bool			operator<(const TypeWrapper<T>& other)	{return value_ < other.value_;}


private:
	T			value_;
};


/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_TYPE_WRAPPER_HPP_INCLUDED__
