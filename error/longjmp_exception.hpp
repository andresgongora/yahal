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


/***********************************************************************************************//**
 * @file longjmp_exception.hpp.
 * @brief Error handling implementation similar to C++ exceptions in C style.
 *
 * Stores all registers and allows their restoration if something goes wrong.
 *
 * @note Braces are optional. Not using them ensures that you dont forget to use ENDTRY
 *
 * @code
 * //Example 1: "ignoring THROW_VAL" and "no braces"
 * TRY
 * foo1();		// Do something
 * THROW(1);		// Throws with value 1.
 * foo2();		// Never reaches this point
 * CATCH
 * 	// Handle error here. The "1" is ignored
 * ENDTRY
 * @endcode
 *
 * @code
 * //Example 2: "throwing a value"
 * TRY
 * {
 * 	foo1();		// Do something
 * 	THROW(3);	// Throws with value 3
 * 	foo2();		// Never reaches this point
 * }
 * CATCH
 * {
 * 	// THROW_VAL can be used to pass an error code
 * 	switch(THROW_VAL)
 * 	{
 * 		case 1: error_handler_1(); break;
 * 		case 2: error_handler_2(); break;
 * 		case 3: error_handler_3(); break;
 * 		default: break;
 * 	}
 * }
 * ENDTRY;
 * @endcode
 **************************************************************************************************/

#ifndef __YAHAL_ERROR_LONGJMP_EXCEPTION_HPP_INCLUDED
#define __YAHAL_ERROR_LONGJMP_EXCEPTION_HPP_INCLUDED


/* ---------------------------------------------------------------------------------------------- */
#include <setjmp.h>
#include <stdint.h>



/* ---------------------------------------------------------------------------------------------- */

/***********************************************************************************************//**
 * @def		TRY
 * @brief	Start exception handling. Stores current system status in "ex_buf__"
 **************************************************************************************************/

/***********************************************************************************************//**
 * @def		CATCH
 * @brief	Handles the throw.
 **************************************************************************************************/

/***********************************************************************************************//**
 * @def		ENDTRY
 * @brief	Ends the try-catch clause.
 **************************************************************************************************/

#define TRY 			do{								\
					jmp_buf ex_buf__;					\
					int16_t THROW_VAL;					\
					if( (THROW_VAL = setjmp(ex_buf__)) == 0)		\
					{	// DO STUFF HERE
#define CATCH 				} else {//switch(THROW_VAL){ case 1: ....
#define ENDTRY				}							\
				}while(0);



/***********************************************************************************************//**
 * @def		THROW(val)
 * @brief	Throws with value "val". It is stored as an int16_t in THROW_VAL
 **************************************************************************************************/

/***********************************************************************************************//**
 * @def		TEST(testvalue)
 * @brief	Test if condition == TRUE, else throw -1, Handy if you ignore THROW_VAL.
 **************************************************************************************************/

#define THROW(val) 		do{longjmp(ex_buf__, val);}while(0) 	// Throw with value



#define TEST(testvalue)		do{if(testvalue == false) THROW(-1);}while(0);



/* ---------------------------------------------------------------------------------------------- */
#endif // __YAHAL_ERROR_LONGJMP_EXCEPTION_HPP_INCLUDED
