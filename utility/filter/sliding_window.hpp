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



#ifndef __SLIDING_WINDOW_HPP_INCLUDED__
#define __SLIDING_WINDOW_HPP_INCLUDED__


/** ---- INCLUDE ------------------------------------------------------------------------------- **/
#include <stdint.h>
#include <cstdlib>



/** ---- NAMESPACE ----------------------------------------------------------------------------- **/
namespace hal{ namespace utility{
	template <class T_data, std::size_t T_bufferSize> class SlidingWindow;
}}



/* ============================================================================================== */
 *	hal::utility::CircularBuffer
 * ============================================================================================== */

template <class T_data, std::size_t T_bufferSize>
class hal::utility::SlidingWindow
{
public:				// CONSTRUCTOR
				SlidingWindow() : _full(false), _index(0) {}



public:				// PUSH & POP
	void			push(T_data data)
				{
					_buffer[_index++] = data;
					if(_index >= maxSize())
					{
						_index = 0;
						_full = true;
					}
				}

	T_data			mean(void)
				{

					T_data aux = 0;		//TODO: WARNING: might overflow
					std::size_t numElements;
					std::size_t i;

					if(_full)	{numElements = maxSize();}
					else		{numElements = _index;}

					if(numElements > 0)
					{
						for(i=0; i<numElements; i++)	{aux += _buffer[i];}
						return aux/numElements;
					}
					else	return 0;




				}

	std::size_t		maxSize(void)
				{
					return T_bufferSize;
				}


	std::size_t		size(void)
				{
					if(_full)	{return maxSize();}
					else		{return _index;}
				}



private:			// PRIVATE VARIABLES
	T_data			_buffer[T_bufferSize];
	bool			_full;
	std::size_t		_index;
};


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__SLIDING_WINDOW_HPP_INCLUDED__
