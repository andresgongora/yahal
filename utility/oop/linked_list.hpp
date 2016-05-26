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
 **************************************************************************************************/
template <typename T_NODE>
class yahal::utility::oop::LinkedListNode
{
protected:
				// CONSTRUCTOR
				LinkedListNode(void) : p_previous_node_(0)	{}

private:
				// FRIEND
	friend class		yahal::utility::oop::LinkedList<T_NODE>;


				/// Set pointer to previous node
	inline void		setPrevious(T_NODE* p_previous_node)
				{
					p_previous_node_ = p_previous_node;
				}


				/// Get pointer to previous node
	inline T_NODE*		getPrevious(void) const
				{
					return p_previous_node_;
				}


				/// Pointer to previous node of same class
	T_NODE*			p_previous_node_;
};




/***********************************************************************************************//**
 * @brief	Linked list of templated type T_NODE.
 *
 *	A LinkedList is composed of a series of instances derived from LinkedListNode,
 *	in which each node points to the previous node.
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
 *	MyClass a;
 *	MyClass b;
 *
 *	// Linked List
 *	LinkedList<MyClass> ll;		// Linked list starts empty
 *
 *	// Linked List manipulation
 *	ll.pushBack(a);			// Add a to list.
 *	ll.pushBack(b);			// Add b to list, linked after a;
 *	ll[0];				// Returns pointer to a;
 *	ll[1]->foo();			// Returns pointer to b and runs b.foo();
 *	ll.size();			// Returns linked list size, equal to 2 in this example
 * @endcode
 *
 **************************************************************************************************/
template <typename T_NODE>
class yahal::utility::oop::LinkedList
{
public:
				/// Constructor.
				LinkedList() :	p_last_node_(NULL),
						size_(0)
				{}


				/// Append node.
	void			pushBack(T_NODE& new_node)
				{
					new_node.setPrevious(p_last_node_);	// New node points to previous node
					p_last_node_ = &new_node;		// New node becomes last node
					size_++;				// List has increased by 1
				}


				/// Retrieve node at given position
	T_NODE*			operator[](std::size_t position) const
				{
					assert(position < size());

					if (position < size_)
					{
						T_NODE*	p_current_node = p_last_node_;

						// Run thorugh the linked list starting at the back
						for (std::size_t i = size_ -1; i>position; i--)
						{
							p_current_node = p_current_node->getPrevious();
						}

						return p_current_node;
					}
					else
					{
						return NULL;
					}
				}


				/// Get size of linked list.
	inline std::size_t	size(void) const
				{
					return size_;
				}


				/// Check if linked list is empty.
	inline bool		isEmpty(void) const
				{
					return (size() == 0);
				}


private:
				// PRIVATE VARIABLES
	T_NODE*			p_last_node_;	///< Pointer to last node, starts being equal to this
	std::size_t		size_;		///< Store size of linked list.
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__
