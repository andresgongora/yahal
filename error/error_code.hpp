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

#ifndef __YAHAL_ERROR_ERROR_CODE_HPP_INCLUDED__
#define __YAHAL_ERROR_ERROR_CODE_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include <cstddef>
#include "../rtos/rtos.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace error{
	class ErrorCode;
}}



/***********************************************************************************************//**
 * @brief	Base class for error code handling.
 *
 * 	This class stores the last error code that happened to a derived class.
 * 	It two public methods to check the existence and value of the last error code
 *	and two protected methods to set and clear the code.
 *	This base class also defines NO_ERROR_CODE (value = NULL) to signal a no error condition.
 *
 *@note		For performance reasons, the error code is stored size_t.
  **************************************************************************************************/
class yahal::error::ErrorCode
{
public:
				/**
				 * @return last error code.
				 */
	std::size_t		getErrorCode(void) const
				{
					_errorMutex.lock();
					unsigned int temp = _errorCode;
					_errorMutex.unlock();
					return temp;
				}

				/**
				 * @return true if last error is not equal to NO_ERROR_CODE.
				 */
	bool			hasError(void) const
				{
					return (getErrorCode() != NO_ERROR_CODE);
				}



protected:
	static const
	std::size_t		NO_ERROR_CODE = 0;	/**< No error condition code.*/


				// CONSTRUCTOR & DESTRUCTOR
				ErrorCode(void) : _errorCode(NO_ERROR_CODE)	{}
	virtual			~ErrorCode(void)			{}

				/**
				 * Set new error code.
				 * Allows derived classes to set a new error code.
				 * @param newErrorCode new error code to store.
				 */
	void			setErrorCode(std::size_t newErrorCode)
				{
					_errorMutex.lock();
					_errorCode = newErrorCode;
					_errorMutex.unlock();
				}

				/**
				 * Clear error code.
				 * Identical to "setErrorCode(NO_ERROR_CODE)".
				 * @see setErrorCode.
				 */
	void			clearErrorCode(void)
				{
					setErrorCode(NO_ERROR_CODE);	// Clears code and count
				}



private:
	volatile std::size_t	_errorCode;	/**< Store last error code .*/
	mutable	yahal::rtos::Mutex _errorMutex;	/**< Thread safety to modify error code .*/
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_ERROR_ERROR_CODE_HPP_INCLUDED__
