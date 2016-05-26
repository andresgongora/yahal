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



#ifndef __YAHAL_UTILITY_FILTER_SLIDING_WINDOW_HPP_INCLUDED__
#define __YAHAL_UTILITY_FILTER_SLIDING_WINDOW_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstdlib>



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace filter{
	template <class T_DATA, std::size_t T_BUFFER_SIZE> class SlidingWindow;
}}}



/***********************************************************************************************//**
 * @brief	Sliding window filter.
 *
 * Add data with push(), and retrieve the mean with mean().
 *
 **************************************************************************************************/
template <class T_DATA, std::size_t T_BUFFER_SIZE>
class yahal::utility::filter::SlidingWindow
{
public:				// CONSTRUCTOR
				SlidingWindow() : index_(0) {}


public:				// PUSH
	void			push(T_DATA data)
				{
					buffer_[index_++] = data;	///< Add new data to buffer
					if(index_ >= maxSize())		///< Determine if at end of buffer
					{
						index_ = 0;		///< Return index to start
						full_ = true;		///< Set full flag permanently to true
					}
				}

	T_DATA			mean(void) const {

					T_DATA aux = 0;
					std::size_t numElements;
					std::size_t i;

					if (full_) 	{numElements = maxSize();}
					else 		{numElements = index_;}

					if (numElements > 0) {
						for (i = 0; i < numElements; i++) {
							aux += buffer_[i];
						}
						return aux / numElements;
					} else {
						return 0;
					}




				}

	std::size_t		maxSize(void) const {
					return T_BUFFER_SIZE;
				}


	std::size_t		size(void) const {
					if (full_) {
						return maxSize();	///< If the buffer is full the index_ can not be used to determine the size
					} else {
						return index_;		///< While filling the buffer up, the size is equal to the index
					}
				}


private:			// PRIVATE VARIABLES
	T_DATA			buffer_[T_BUFFER_SIZE];
	bool			full_;
	std::size_t		index_;
};


/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_UTILITY_FILTER_SLIDING_WINDOW_HPP_INCLUDED__
