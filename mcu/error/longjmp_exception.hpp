// 1 TAB = 8 SPACES //

      /**
	*	ID:	LONGJMP_EXCEPTION
	*   EDITED:	21-04-2015
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|	Error handling implementation similar to C++ exceptions in C style	|
	*	|										|
	*	|	Implements:								|
	*	|	- TRY:		Start the try. Can THROW inside it			|
	*	|	- CATCH:	Handles the throw					|
	*	|	- ENDTRY:	Ends the try-catch clause				|
	*	|	- THROW(val):	Throws with value "val". Usefull to pass an error code	|
	*	|	- THROW:	Throws with default value -1				|
	*	|	- THROW_VAL:	int16_t that contains the throw value			|
	*	|										|
	*	|	NOTE:	braces are optional. Not using them ensures that you dont	|
	*	|		forget to use ENDTRY						|
	*	|										|
	*	|	-----------------------------------------------------------------	|
	*	|										|
	*	|	Example 1: "ignoring THROW_VAL" and "no braces"				|
	*	|	TRY									|
	*	|		foo1();		// Do something					|
	*	|		THROW(1);	// Throws with value 1.				|
	*	|		foo2();		// Never reaches this point			|
	*	|	CATCH									|
	*	|		// Handle error. The "1" is ignored				|
	*	|	ENDTRY									|
	*	|										|
	*	|	-----------------------------------------------------------------	|
	*	|										|
	*	|	Example 2: "throwing a value"						|
	*	|	TRY									|
	*	|	{									|
	*	|		foo1();		// Do something					|
	*	|		THROW(3);	// Throws with value 3				|
	*	|		foo2();		// Never reaches this point			|
	*	|	}									|
	*	|	CATCH									|
	*	|	{									|
	*	|		// THROW_VAL can be used to pass an error code			|
	*	|		switch(THROW_VAL)						|
	*	|		{								|
	*	|			case 1: error_handler_1(); break;			|
	*	|			case 2: error_handler_2(); break;			|
	*	|			case 3: error_handler_3(); break;			|
	*	|			default: break;						|
	*	|		}								|
	*	|	}									|
	*	|	ENDTRY;									|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/


#ifndef __LONGJMP_EXCEPTION_HPP_INCLUDED
#define __LONGJMP_EXCEPTION_HPP_INCLUDED


//----- INCLUDE ------------------------------------------------------------------------------------
#include <setjmp.h>
#include <stdint.h>



//----- DEFINE -------------------------------------------------------------------------------------

#define TRY 			do{								\
					jmp_buf ex_buf__;					\
					int16_t THROW_VAL;					\
					if( (THROW_VAL = setjmp(ex_buf__)) == 0)		\
					{	// DO STUFF HERE
#define CATCH 				} else {//switch(THROW_VAL){ case 1: ....
#define ENDTRY				}							\
				}while(0);



#define THROW(val) 		do{longjmp(ex_buf__, val);}while(0) 	// Throw with value



#define TEST(testvalue)		do{if(testvalue == false) THROW(-1);}while(0);


#endif //__LONGJMP_EXCEPTION_HPP_INCLUDED


