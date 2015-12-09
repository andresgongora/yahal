// 1 TAB = 8 SPACES //

      /**
	*	ID:	circular_buffer.hpp
	*   EDITED:	21/11/2015
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|	FIFO CIRCULAR BUFFER							|
	*	|										|
	*	|	Can hold T_BUFFER_SIZE -1 elements of type T_DATA			|
	*	|										|
	*	|	- push : push next element to end buffer (returns true if successful)	|
	*	|	- pop:	 move first (oldest) element out of the buffer (delete it)	|
	*	|	- peek:	 get first (oldest) element without deleting it			|
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


#ifndef __MCU_CIRCULAR_BUFFER_HPP_INCLUDED__
#define __MCU_CIRCULAR_BUFFER_HPP_INCLUDED__


/** ---- INCLUDE ------------------------------------------------------------------------------- **/
#include <cstdlib>



/** ---- NAMESPACE ----------------------------------------------------------------------------- **/
namespace mcu{ namespace utility{
	template <class T_DATA, std::size_t T_BUFFER_SIZE> class CircularBuffer;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::utility::CircularBuffer
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

template <class T_DATA, std::size_t T_BUFFER_SIZE>
class hal::utility::CircularBuffer : public error::ErrorCode
{
public:				// CONSTRUCTOR
				CircularBuffer() : 	_pPush(0), _pPop(0)	{}



public:				// PUBLIC STATUS
	bool			isEmpty(void) const{
					return (_pPush == _pPop) ? true : false;
				}

	bool			isFull(void) const{
					return (size() == maxSize()) ? true : false;
				}



public:				// PUSH & POP
	bool			push(T_DATA data){
					if(not isFull())
					{
						_buffer[_pPush++] = data;
						if(_pPush > maxSize()){_pPush = 0;}
						return true;
					}
					else return false;
				}

	T_DATA 			pop(void){
					T_DATA data = 0;

					if(not isEmpty())
					{
						data = _buffer[_pPop++];
						if(_pPop > maxSize()){_pPop = 0;}
					}

					return data;
				}

	T_DATA			peek(void){
					T_DATA data = 0;
					if(not isEmpty()){data = _buffer[_pPop];}
					return data;
				}



private:			// PRIVATE STATUS
	std::size_t		maxSize(void) const{
					return T_BUFFER_SIZE-1;
				}

	std::size_t		size(void) const{
					if(isEmpty())		return 0;
					else if(_pPush > _pPop) return _pPush - _pPop;
					else		   	return (T_BUFFER_SIZE+_pPush)-_pPop;
				}



private:			// PRIVATE VARIABLES -----------------------------------------------
	T_DATA			_buffer[T_BUFFER_SIZE];
	std::size_t		_pPush;
	std::size_t		_pPop;
};



/** ============================================================================================ **/
#endif 	//__MCU_CIRCULAR_BUFFER_HPP_INCLUDED__
