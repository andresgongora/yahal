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

#ifndef __YAHAL_UTILITY_OOP_PUBLISH_SUBSCRIBE_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_PUBLISH_SUBSCRIBE_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <cstdlib>
#include "linked_list.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	template <typename T_MSG> class Publisher;
	template <> class Publisher<void>;

	template <typename T_MSG> class Subscriber;
	template <> class Subscriber<void>;
}}}



/***********************************************************************************************//**
 * @brief	Publisher base class. This class notifies all subscribers.
 *
 *
 * @code
 * 	// Messages, for example an enum, but it could be any class
 * 	enum MyCode{
 * 		NOTHING,
 * 		SUCCESS,
 * 		GOAL,
 * 		IMOUTOFIDEAD
 * 	};
 *
 * 	// Publisher class
 * 	class Newsletter : public Publisher<MyCode>
 * 	{
 * 		...
 * 	}
 *
 * 	// Subscriber
 * 	class Reader : public Subscriber<MyCode>
 * 	{
 * 		// Do stuff when a message is received.
 * 		virtual notify(MyCode message){ ... } *
 * 	}
 *
 * 	main()
 * 	{
 * 		Newsletter dayly_sports;		// Publisher
 * 		Reader	john;				// Subscriber
 * 		Reader	mikel;				// Subscriber
 *
 * 		// Subscriptions
 * 		john.subscribeTo(&dayly_sports);	// A subscriber may subscribe: valid
 * 		dayly_sports.subscribe(&mikel);		// A publisher may be subscribed to: valid
 *
 * 		dayly_sports.publish(GOAL);		// All subscribers receive a message GOAL
 * 	}
 *
 **************************************************************************************************/
template <typename T_MSG>
class yahal::utility::oop::Publisher
{
public:
				/// Used by Subscribers to subscribe.
	void			subscribe(yahal::utility::oop::Subscriber<T_MSG>* p_new_subscriber)
				{
					subscribers_.pushBack(p_new_subscriber);
				}

				/// Tublish a message to all subscribers
	void			publish(T_MSG message) const
				{
					std::size_t size = subscribers_.size();	///< Get number of subscribers
					std::size_t i;

					for (i = 0; i < size; i++) {
						subscribers_[i]->notify(message);
					}
				}


private:
				/// Linked list of type Subscribers
	yahal::utility::oop::LinkedList< yahal::utility::oop::Subscriber<T_MSG> > subscribers_;
};






/***********************************************************************************************//**
 * @brief	Subscriber base class. Any derived class can subscribe to subscribers of type T_MSG.
 *
 *	A subscriber can subscribe to various publishers. But right now there is no way to know
 * 	the source of a message.
 **************************************************************************************************/
template <typename T_MSG>
class yahal::utility::oop::Subscriber :
	public yahal::utility::oop::LinkedListNode<yahal::utility::oop::Subscriber<T_MSG> >
{
protected:
				// CONSTRUCTOR
				Subscriber(void)		{}


private:
				/// FRONT END ACCESIBLE ONLY BY PUBLISHER
	friend class		yahal::utility::oop::Publisher<T_MSG>;

				/// This function receives any published message.
				/// Todo: mecahnism to detect source publisher.
	virtual void		notify(T_MSG message) = 0;



public:
				/// Subscribe to publisher
	void			subscribeTo(yahal::utility::oop::Publisher<T_MSG>* p_publisher){
					p_publisher->subscribe(this);
				}
};



/***********************************************************************************************//**
 * @brief	Subscriber void specialization.
 **************************************************************************************************/
template <>
class yahal::utility::oop::Subscriber<void> :
	public yahal::utility::oop::LinkedListNode<yahal::utility::oop::Subscriber<void> >
{
protected:
				Subscriber(void);

private:
	friend class		yahal::utility::oop::Publisher<void>;
	virtual void		notify(void) = 0;

public:
	void			subscribeTo(yahal::utility::oop::Publisher<void>* p_publisher);
};



/***********************************************************************************************//**
 * @brief	Publisher void specialization.
 **************************************************************************************************/
template<>
class yahal::utility::oop::Publisher<void>
{
public:
				/// Used by Subscribers to subscribe.
	void			subscribe(yahal::utility::oop::Subscriber<void>* p_new_subscriber)
				{
					subscribers_.pushBack(p_new_subscriber);
				}

				/// Tublish a message to all subscribers
	void			publish(void) const
				{
					std::size_t size = subscribers_.size();	///< Get number of subscribers
					std::size_t i;

					for (i = 0; i < size; i++) {
						subscribers_[i]->notify();
					}
				}


private:
				/// Linked list of type Subscribers
	yahal::utility::oop::LinkedList< yahal::utility::oop::Subscriber<void> > subscribers_;

};


// Not elegant, but I did this to avoid linking errors
inline void yahal::utility::oop::Subscriber<void>::subscribeTo(yahal::utility::oop::Publisher<void>* p_publisher)
{
	p_publisher->subscribe(this);
}

/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_PUBLISH_SUBSCRIBE_HPP_INCLUDED__
