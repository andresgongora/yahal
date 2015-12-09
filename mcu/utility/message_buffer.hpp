// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
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

	/* 	TODO: DEFINE VS ENUM
	*/


#ifndef __MESSAGE_BUFFER_HPP_INCLUDED__
#define __MESSAGE_BUFFER_HPP_INCLUDED__


/** ---- INCLUDE ------------------------------------------------------------------------------- **/
#include <stdint.h>
#include <cstdlib>
#include "hal/error/error_code.hpp"



/** ---- NAMESPACE ----------------------------------------------------------------------------- **/
namespace hal{ namespace utility{
	template <class T_data, std::size_t T_bufferSize> class MessageBuffer;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::utility::MessageBuffer
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

template <class T_data, std::size_t T_bufferSize>
class hal::utility::MessageBuffer : public error::ErrorCode
{
public:				// ERROR CODES -----------------------------------------------------
				struct ERROR{ enum type{
					NONE = 0,

					STACKT_BUFFER_SIZE_TOO_SMALL,
					MESSAGE_SIZE_ZERO,
					MESSAGE_SIZE_OVERT_BUFFER_SIZE,

					MESSAGE_DATA_SOURCE_NULL_POINTER,
					MESSAGE_DATA_DESTINY_NULL_POINTER,

					PUSH_OVERFLOW_ATTEMPT,
					POP_OVERFLOW_ATTEMPT,
					POP_NOT_FULLY_PUSHED_BUFFER_ATTEMPT,

					OTHER,
				};};



public:				// CONSTRUCTOR -----------------------------------------------------
				MessageBuffer() : 	_messageSize(0),
							_numPushed(0),
							_numPopped(0)
				{}



public:				// STATUS ----------------------------------------------------------
	std::size_t		getSize(void)		const {return _messageSize;}
	std::size_t		getMaxSize(void)	const {return T_bufferSize;}

	std::size_t		getRemainingPushes(void)const {return _messageSize - _numPushed;}
	bool			allPushed(void)		const {return _numPushed >= _messageSize;}

	std::size_t		getRemainingPops(void)	const {return _messageSize - _numPopped;}
	bool			allPopped(void)		const {return _numPopped >= _messageSize;}



public:				// INITIALIZATION --------------------------------------------------
	bool			init(std::size_t messageSize)
				{
					this->clearErrorCode();		// Clear old error code
					_messageSize = 0;
					_numPushed = 0;
					_numPopped = 0;

					if(T_bufferSize < sizeof(T_data))
					{
						setErrorCode(ERROR::STACKT_BUFFER_SIZE_TOO_SMALL);
					}
					else
					{
						clear();		// Wipe old data from buffer
						setSize(messageSize);	// Set message size
					}

					return hasError();		// For future debugging
				}



public:				// PUSH & POP ------------------------------------------------------
	bool 			push(T_data data)
				{
					if(allPushed())
					{
						setErrorCode(ERROR::PUSH_OVERFLOW_ATTEMPT);
					}
					else
					{
						_buffer[_numPushed++] = data;
					}
					return hasError();
				}

	bool			push(T_data* pSource, std::size_t size)
				{
					if(pSource == 0)
					{
						setErrorCode(ERROR::MESSAGE_DATA_SOURCE_NULL_POINTER);
					}
					else
					{
						for(std::size_t i = 0; i<size; i++)
							push(pSource[i]);
					}
					return hasError();
				}

	T_data 			pop(void)
				{
					T_data data = 0;

					if(allPushed()==false)
					{
						setErrorCode(ERROR::POP_NOT_FULLY_PUSHED_BUFFER_ATTEMPT);
					}
					else if(allPopped())
					{
						setErrorCode(ERROR::POP_OVERFLOW_ATTEMPT);
					}
					else
					{
						data = _buffer[_numPopped++];
					}

					return data;
				}

	bool			pop(T_data* pDestiny, std::size_t size)
				{
					if(pDestiny == 0)
					{
						setErrorCode(ERROR::MESSAGE_DATA_DESTINY_NULL_POINTER);
					}
					else
					{
						for(std::size_t i = 0; i<size; i++)
							pDsestiny[i] = pop();
					}
					return hasError();
				}



public:				// RETRY TRANSMISSION FROM BEGINNING -------------------------------
	bool			resetPops(void)
				{
					_numPopped = 0;
					return hasError();
				}



private:			// SET I/O SIZE ----------------------------------------------------
	bool 			setSize(std::size_t size)
				{
					if(size > T_bufferSize)
					{
						setErrorCode(ERROR::MESSAGE_SIZE_OVERT_BUFFER_SIZE);
					}
					else if(size == 0)
					{
						setErrorCode(ERROR::MESSAGE_SIZE_ZERO);
					}
					else
					{
						_messageSize = size;
					}
					return hasError();
				}



private:			// INITIALIZE STACK DATA -------------------------------------------
	void 			clear(T_data defaultValue = 0)
				{
					for(std::size_t i = 0; i<T_bufferSize; i++)
						_buffer[i] = defaultValue;
				}



private:			// PRIVATE VARIABLES -----------------------------------------------
	T_data			_buffer[T_bufferSize];
	std::size_t		_messageSize;
	volatile std::size_t	_numPushed;
	volatile std::size_t	_numPopped;
};


/** ============================================================================================ **/
#endif 	//__MESSAGE_BUFFER_HPP_INCLUDED__
