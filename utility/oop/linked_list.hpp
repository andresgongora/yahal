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

#ifndef __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <cstdlib>
#include "../../error/assert.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	template <typename T_NODE> class LinkedListNode;
	template <typename T_NODE> class LinkedList;
}}}



/***********************************************************************************************//**
 * @brief	Base class for classes that can be linked in a LinkedList
 *
 *	The Curiously Recurring Template Pattern is used to acces the derived class T_NODE.
 *	All methods for LinkedListNode are private and only accesible by LinkedList.
 *
 * @todo	assert((std::is_base_of<LinkedListNode<T_NODE>, T_NODE>::value));
 **************************************************************************************************/
template <typename T_NODE>
class yahal::utility::oop::LinkedListNode
{
protected:
				// CONSTRUCTOR
				 LinkedListNode(void) : p_next_node_(0)	{}
	virtual			~LinkedListNode(void)			{}


private:
				// FRIEND
	friend class		yahal::utility::oop::LinkedList<T_NODE>;


				/// Set pointer to next node
	void			setNext(T_NODE* p_next_node)
				{
					p_next_node_ = p_next_node;
				}


				/// Get pointer to next node
	T_NODE*			getNext(void) const
				{
					return p_next_node_;
				}


				/// Pointer to next node of same class
	T_NODE*			p_next_node_;
};




/***********************************************************************************************//**
 * @brief	Linked list of templated type T_NODE.
 *
 *	A LinkedList is composed of a series of classes deroved from LinkedListNodes,
 *	in which each node points to the next node.
 *
 *	The function of the LinkedList is to provide methods to navigate to the desired node,
 *	control the total ammount of linked nodes and allow adding new nodes to the list.
 *
 * @code
 *	// Class example we want to link in a list. Must derive from LinkedListNode
 *	class MyClass : public LinkedListNode<MyClass>
 *	{
 *	public:
 *		void foo(void) { ... }
 *		int number;
 *	}
 *
 *	// Nodes that will be linked
 *	MyClassNode a;
 *	MyClassNode b;
 *
 *	// Linked List
 *	LinkedList<MyClass> ll;		// Linked list starts empty
 *
 *	// Linked List manipulation
 *	ll.pushBack(a);			// Add a to list.
 *	ll.pushBack(b);			// Add b to list, linked after a;
 *	ll[0];				// Returns pointer to a;
 *	ll[1]->foo();			// Returns pointer to b and runs b.foo();
 *	ll.size();			// Returns linked list size, equal to 2
 * @endcode
 **************************************************************************************************/
template <typename T_NODE>
class yahal::utility::oop::LinkedList
{
public:
				/// Constructor.
				LinkedList()	: p_first_node_(0), size_(0)	{}


				/// Append node.
	void			pushBack(T_NODE* p_new_node)
				{
					if (isEmpty()) {
						p_first_node_ = p_new_node;
					} else {
						lastNode()->setNext(p_new_node);
					}

					size_++;
				}



public:
				/// Retrieve node.
	T_NODE*			operator[](std::size_t position) const
				{
					T_NODE*	p_current_node = p_first_node_;

					if (position >= size_) {
						/// Try to detect this error in debug mode
						_DEBUG_TRAP();

						/// If trying to access non-existant node,
						/// point instead to last node instead.
						/// Its not an optimum solution.
						position = size_ -1;
					}

					for (std::size_t i = position; i; i--) {
						p_current_node = p_current_node->getNext();
					}

					return p_current_node;
				}



				/// Check if linked list is empty.
	bool			isEmpty(void) const
				{
					return (p_first_node_ == 0);
				}

				/// Get size of linked list.
	std::size_t		size(void) const
				{
					return size_;
				}


private:
				/// Retrieve last node, even if it is empty.
	T_NODE*			lastNode(void) const
				{
					if (isEmpty()) {
						return p_first_node_;
					} else {
						return this->operator[](size_ - 1);
					}
				}



private:			// PRIVATE VARIABLES
	T_NODE*			p_first_node_;	///< Pointer to first node, starts empty.
	std::size_t		size_;		///< Store size of linked list.
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__
