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



#ifndef __ERROR_CODE_HPP_INCLUDED__
#define __ERROR_CODE_HPP_INCLUDED__

//TODO: Poder indicar source, error verbose, etc. http://programmers.stackexchange.com/questions/262019/is-it-good-practice-to-rely-on-headers-being-included-transitively

/* ---------------------------------------------------------------------------------------------- */
#include "../rtos/rtos.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace error{
	class ErrorCode;
}}



/* ============================================================================================== */
 *	error::ErrorCode
 * ============================================================================================== */

class yahal::mcu::error::ErrorCode
{
public:				// CONST -----------------------------------------------------------
	static const
	unsigned int		NO_ERROR = 0;



protected:			// CONSTRUCTOR & DESTRUCTOR ----------------------------------------
				ErrorCode(void) : _errorCode(NO_ERROR)	{}
	virtual			~ErrorCode(void)			{}



public:				// PUBLIC API ------------------------------------------------------
	unsigned int		getErrorCode(void) const
				{
					_errorMutex.lock();
					unsigned int temp = _errorCode;
					_errorMutex.unlock();
					return temp;
				}

	bool			hasError(void) const
				{
					return (getErrorCode() != NO_ERROR);
				}



protected:			// PROTECTED API ---------------------------------------------------
	void			setErrorCode(unsigned int newErrorCode)
				{
					_errorMutex.lock();
					_errorCode = newErrorCode;
					_errorMutex.unlock();
				}

	void			clearErrorCode(void)
				{
					setErrorCode(NO_ERROR);	// Clears code and count
				}



private:			// PRIVATE VARIABLES -----------------------------------------------
	volatile unsigned int	 _errorCode;
	mutable	mcu::rtos::Mutex _errorMutex;
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__ERROR_CODE_HPP_INCLUDED__
