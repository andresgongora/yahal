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
