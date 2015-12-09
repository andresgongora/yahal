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


#ifndef __MESSAGESTACK_HPP_INCLUDED__
#define __MESSAGESTACK_HPP_INCLUDED__


/** ---- INCLUDE ------------------------------------------------------------------------------- **/
#include <stdint.h>
#include <cstdlib>
#include "hal/error/error_code.hpp"



/** ---- NAMESPACE ----------------------------------------------------------------------------- **/
namespace hal{ namespace utility{
	template <class T_data, std::size_t T_stackSize> class MessageStack;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::utility::MessageStack
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

template <class T_data, std::size_t T_stackSize>
class hal::utility::MessageStack : public error::ErrorCode
{
public:				// CONFIG VALUES ---------------------------------------------------
				struct DIRECTION{ enum type{
					INCOMING = false,
					OUTGOING = true,
				};};



				// ERROR CODES -----------------------------------------------------
				struct ERROR{ enum type{
					NONE = 0,

					STACK_MAX_SIZE_TOO_SMALL,

					MESSAGE_SIZE_ZERO,
					MESSAGE_SIZE_OVER_MAX_SIZE,
					MESSAGE_DATA_SOURCE_NULL_POINTER,
					MESSAGE_DATA_DESTINY_NULL_POINTER,

					PULL_OVERFLOW_ATTEMPT,
					PULL_INCOMING_STACK_ATTEMPT,

					PUSH_OVERFLOW_ATTEMPT,
					PUSH_OUTGOING_STACK_ATTEMPT,

					LOAD_INCOMING_STACK_ATTEMPT,
					UNLOAD_OUTGOING_STACK_ATTEMPT,
					UNLOAD_UNFINISHED_RX_ATTEMPT,

					OTHER,
				};};



public:				// CONSTRUCTOR -----------------------------------------------------
				MessageStack() : 	_size(0),
							_MAX_SIZE(T_stackSize),
							_transferred(0),
							_direction(DIRECTION::OUTGOING)
				{}



public:				// STATUS ----------------------------------------------------------
	std::size_t		getSize(void)		const {return _size;}
	std::size_t		getMaxSize(void)	const {return _MAX_SIZE;}
	std::size_t		getRemainingBytes(void) const {return _size - _transferred;}
	bool			done(void)		const {return _transferred >= _size;}



public:				// TRANSMISSION INITIALIZATION -------------------------------------
	bool 			initOutgoing(T_data* pData, std::size_t size)
				{
					_direction = DIRECTION::OUTGOING;

					// TRY SUCCESIVELY. YIELD AFTER FIRST ERROR
					if	(init() == false)		{}
					else if	(setSize(size) == false)	{}
					else if	(load(pData) == false)		{}
					else					{}

					return hasError();
				}

	bool 			initIncoming(std::size_t size)
				{
					_direction = DIRECTION::INCOMING;

					// TRY SUCCESIVELY. YIELD AFTER FIRST ERROR
					if	(init() == false)		{}
					else if	(setSize(size) == false)	{}
					else					{}

					return hasError();
				}



public:				// BYTE ACCESS -----------------------------------------------------
	void 			push(T_data data)
				{
					if(done())
					{
						setErrorCode(ERROR::PUSH_OVERFLOW_ATTEMPT);
					}
					else if(_direction == DIRECTION::OUTGOING)
					{
						setErrorCode(ERROR::PUSH_OUTGOING_STACK_ATTEMPT);
					}
					else
					{
						stack[_transferred] = data;
						_transferred++;
					}
				}

	T_data 			pull(void)
				{
					T_data data = 0;

					if(done())
					{
						setErrorCode(ERROR::PULL_OVERFLOW_ATTEMPT);
					}
					else if(_direction == DIRECTION::INCOMING)
					{
						setErrorCode(ERROR::PULL_INCOMING_STACK_ATTEMPT);
					}
					else
					{
						data = stack[_transferred];
						_transferred++;
					}

					return data;
				}



public:				// ACCESS FINISHED INCOMING TRANSMISSION ---------------------------
	bool 			unload(T_data* pDestiny)
				{
					if(pDestiny == 0)
					{
						setErrorCode(ERROR::MESSAGE_DATA_DESTINY_NULL_POINTER);
					}
					else if(_direction == DIRECTION::OUTGOING)
					{
						setErrorCode(ERROR::UNLOAD_OUTGOING_STACK_ATTEMPT);
					}
					else if(done())
					{
						setErrorCode(ERROR::UNLOAD_UNFINISHED_RX_ATTEMPT);
					}
					else
					{
						std::memcpy(pDestiny, _stack, _size);
					}

					return hasError();
				}



public:				// RETRY TRANSMISSION FROM BEGINNING -------------------------------
	bool			reset(void)
				{
					_transferred = 0;
					return hasError();
				}



private:			// DEFAULT VALUES --------------------------------------------------
	bool			init()
				{
					this->clearErrorCode();		// Clear old error code

					if(_MAX_SIZE < sizeof(T_data))
					{
						setErrorCode(ERROR::STACK_MAX_SIZE_TOO_SMALL);
					}
					else
					{
						clear();		// Wipe old data from stack
						_transferred = 0;	// No I/O yet
						_size = 0;		// Default to 0
					}

					return hasError();		// For future debugging
				}



private:			// SET I/O SIZE ----------------------------------------------------
	bool 			setSize(std::size_t size)
				{
					if(size > _MAX_SIZE)
					{
						setErrorCode(ERROR::MESSAGE_SIZE_OVER_MAX_SIZE);
					}
					else if(size == 0)
					{
						setErrorCode(ERROR::MESSAGE_SIZE_ZERO);
					}
					else
					{
						_size = size;
					}
					return hasError();
				}



private:			// INITIALIZE STACK DATA -------------------------------------------
	void 			clear(T_data defaultValue = 0)
				{
					for(std::size_t i = 0; i<_MAX_SIZE; i++)
						_stack[i] = defaultValue;
				}

	bool 			load(T_data* pSource)
				{
					if(pSource == 0)
					{
						setErrorCode(ERROR::MESSAGE_DATA_SOURCE_NULL_POINTER);
					}
					else if(_direction == DIRECTION::INCOMING)
					{
						setErrorCode(ERROR::LOAD_INCOMING_STACK_ATTEMPT);
					}
					else
					{
						std::memcpy(_stack, pSource, _size);
					}
					return hasError();
				}



private:			// PRIVATE VARIABLES -----------------------------------------------
	T_data			_stack[T_stackSize];
	std::size_t		_size;
	volatile std::size_t	_transferred;
	bool			_direction;
	const std::size_t 	_MAX_SIZE;
};


/** ============================================================================================ **/
#endif 	//__MESSAGESTACK_HPP_INCLUDED__
