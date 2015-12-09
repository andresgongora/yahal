// 1 TAB = 8 SPACES //

      /**
	*	ID:	ErrorCode.hpp
	*   EDITED:	8-10-2015
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|	Base class for error handling						|
	*	|	Returns the last error code when prompted				|
	*	|	0 = No error = Initial value						|
	*	|										|
	*	|	It is also possible to count the number of errors that have happened	|
	*	|	since the last time that ErrorCode has been cleared.			|
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


#ifndef __ERROR_CODE_HPP_INCLUDED__
#define __ERROR_CODE_HPP_INCLUDED__

//TODO: Poder indicar source, error verbose, etc. http://programmers.stackexchange.com/questions/262019/is-it-good-practice-to-rely-on-headers-being-included-transitively

/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../rtos/rtos.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace error{
	class ErrorCode;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	error::ErrorCode
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::error::ErrorCode
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



/** ============================================================================================ **/
#endif 	//__ERROR_CODE_HPP_INCLUDED__
