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




#ifndef __PUBLISH_SUBSCRIBE_HPP_INCLUDED__
#define __PUBLISH_SUBSCRIBE_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <cstdlib>
#include "linked_list.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace utility
{
	template <typename T_MSG> class Publisher;
	template <typename T_MSG> class Subscriber;
}}



/* ============================================================================================== */
 *	utility::Publisher
 * ============================================================================================== */

template <typename T_MSG>
class hal::utility::Publisher
{
public:
	void			subscribe(hal::utility::Subscriber<T_MSG>& newSubscriber)
				{
					_subscribers.pushBack(newSubscriber);
				}

	void			publish(T_MSG message) const
				{
					std::size_t size = _subscribers.size();
					std::size_t i;

					for(i=0; i<size; i++)
					{
						_subscribers[i]->notify(message);
					}
				}


private:
				// PRIVATE VARIABLES
	hal::utility::LinkedList<hal::utility::Subscriber<T_MSG> >	_subscribers;
};



/* ============================================================================================== */
 *	hal::utility::SignalHandler
 * ============================================================================================== */

template <typename T_MSG>
class hal::utility::Subscriber : public hal::utility::LinkedListNode<Subscriber<T_MSG> >
{
public:
				// CONSTRUCTOR & DESTRUCTOR
				Subscriber(void)		{}


private:
				// FRONT END ACCESIBLE ONLY BY PUBLISHER
	friend class		hal::utility::Publisher<T_MSG>;
	virtual void		notify(T_MSG message) = 0;
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __PUBLISH_SUBSCRIBE_HPP_INCLUDED__
