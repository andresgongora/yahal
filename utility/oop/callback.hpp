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

#ifndef __YAHAL_CALLBACK_HPP_INCLUDED__
#define __YAHAL_CALLBACK_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	template <typename T_ARGUMENT> class Callback;
}}}




/***********************************************************************************************//**
 * @brief	Simple callback function subscription that accepts one templated argument.
 *
 * This class acts as a wrapper for a function pointer.
 * The function to be called can be changed and run with separate member functions.
 * The functions must return void and accept one single parameter of type T_ARGUMENT,
 * which is passed as the callback argument.
 *
 * @param	T_ARGUMENT is the type of the argument used to call the function
 **************************************************************************************************/
template <typename T_ARGUMENT>
class yahal::utility::oop::Callback
{
public:				// CONSTRUCTOR & DESTRUCTOR
				Callback() : _fpCallBackFunction(NULL)	{}



public:				// CALLBACK API
	void			setCallBackFunction( void(*fpCallOnTrigger)(T_ARGUMENT) ){
					_fpCallBackFunction = fpCallOnTrigger;
				}

				/// Run callback function. Return true if called.
	bool			run(T_ARGUMENT argument) const{
					bool fpCalled = false;
					if(_fpCallBackFunction != 0)
					{
						_fpCallBackFunction(argument);
						fpCalled = true;
					}
					return fpCalled;
				}



private:			// PRIVATE VARIABLES
				void(*_fpCallBackFunction)(T_ARGUMENT);
};



/***********************************************************************************************//**
 * @brief	Simple callback function subscription that accepts no argument and returns void.
 **************************************************************************************************/
template <>
class yahal::utility::oop::Callback<void>
{
public:				// CONSTRUCTOR & DESTRUCTOR
				Callback() : _fpCallBackFunction(NULL)	{}



public:				// CALLBACK API
	void			setCallBackFunction( void(*fpCallOnTrigger)(void) ){
					_fpCallBackFunction = fpCallOnTrigger;
				}

				/// Run callback function. Return true if called.
	bool			run(void) const{
					bool fpCalled = false;
					if(_fpCallBackFunction != 0)
					{
						_fpCallBackFunction();
						fpCalled = true;
					}
					return fpCalled;
				}



private:			// PRIVATE VARIABLES
				void(*_fpCallBackFunction)(void);
};





/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_CALLBACK_HPP_INCLUDED__
