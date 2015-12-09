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



#ifndef __MCU_CALLBACK_HPP_INCLUDED__
#define __MCU_CALLBACK_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace utility{
	template <typename T_ARGUMENT> class Callback;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	utility::Callback
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ============================================================================== WITH ARGUMENT **/

template <typename T_ARGUMENT>
class mcu::utility::Callback
{
public:				// CONSTRUCTOR & DESTRUCTOR
				Callback() : _fpCallBackFunction(NULL)	{}



public:				// CALLBACK API
	void			setCallBackFunction( void(*fpCallOnTrigger)(T_ARGUMENT) ){
					_fpCallBackFunction = fpCallOnTrigger;
				}

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



/** =========================================================================== WITHOUT ARGUMENT **/

template <>
class mcu::utility::Callback<void>
{
public:				// CONSTRUCTOR & DESTRUCTOR
				Callback() : _fpCallBackFunction(NULL)	{}



public:				// CALLBACK API
	void			setCallBackFunction( void(*fpCallOnTrigger)(void) ){
					_fpCallBackFunction = fpCallOnTrigger;
				}

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




/** ============================================================================================ **/
#endif 	// __MCU_CALLBACK_HPP_INCLUDED__
