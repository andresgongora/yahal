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




#ifndef __COUNTER_HPP_INCLUDED__
#define __COUNTER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <limits>
//#include "hal/utility/embedded_mutex.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace hal{ namespace utility
{
	template <typename T> class Counter;
}}



/* ============================================================================================== */
 *	utility::Counter
 * ============================================================================================== */

template <typename T>
class hal::utility::Counter
{
public:
				// CONSTRUCTOR
				Counter()			: _value(0)		{}
//	explicit		Counter(int initialValue)	: _value(initialValue)	{}


	T			getValue(void) const
				{
					_mutex.lock();
					T temp = _value;
					_mutex.unlock();
					return temp;
				}

	void			clear(void)
				{
					_mutex.lock();
					_value = 0;
					_mutex.unlock();
				}


	Counter			operator++(int)		{return add(1);}

private:
//	void			operator--(void)		{add(-1);}


	Counter			add(T number)
				{
					_mutex.lock();

					// GET MAX AND MIN VALUES
					const T max = std::numeric_limits<T>::max();
					const T min = std::numeric_limits<T>::min();

					// CHECK FOR OVERFLOW
					if	(number > 0 && _value > max - number);	// Overflow
					else if (number < 0 && _value < min - number);	// Underflow
					else	_value += number;			// All OK

					_mutex.unlock();

					Counter temp(*this);
					return temp;
				}


private:
	T			_value;

	mutable
	utility::EmbeddedMutex	_mutex;

};




/* ---------------------------------------------------------------------------------------------- */
#endif 	// __COUNTER_HPP_INCLUDED__
