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

#ifndef __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__
#define __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <cstdlib>
#include "../../error/assert.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace oop{
	template <typename T> class LinkedListNode;
	template <typename T> class LinkedList;
}}}





/***********************************************************************************************//**
 * @brief	Individual node of a linked list. Its type is T_NODE.
 *
 *	A LinkedListNode derives from T_NODE, and thus allows access to the base class.
 **************************************************************************************************/
template <typename T_NODE>
class yahal::utility::oop::LinkedListNode :
		public T_NODE
{
public:
				// CONSTRUCTOR
				LinkedListNode() : _pNextNode(0)
				{}


private:
				// FRIEND
	friend class		yahal::utility::oop::LinkedList<T_NODE>;


				/// Set pointer to next node
	void			setNext(LinkedListNode<T_NODE>& nextNode)
				{
					_pNextNode = &nextNode;
				}


				/// Get pointer to next node
	LinkedListNode<T_NODE>*	getNext(void) const
				{
					return _pNextNode;
				}


				/// Pointer to next node of same class
	LinkedListNode<T_NODE>*	_pNextNode;
};




/***********************************************************************************************//**
 * @brief	Linked list of templated type T_NODE.
 *
 *	A LinkedList is composed of a series of LinkedListNodes, in which each node points
 *	to the next node.
 *
 *	The function of the LinkedList is to provide methods to navigate to the desired
 *	LinkedListNode, control the total ammount of linked nodes and allow adding new
 *	nodes to the list.
 *
 * @code
 *	// Class example we want to link in a list
 *	class MyClass {
 *	public:
 *		void foo(void) { ��� }
 *		int number;
 *	}
 *
 *	// Nodes that will be linked
 *	typedef LinkedListNode<MyClass> MyClassNode;
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
public:				// CONSTRUCTOR
				LinkedList()	: _pFirstNode(0), _size(0)	{}


				/// APPEND NODE
	void			pushBack(LinkedListNode<T_NODE>& newNode)
				{
					if (isEmpty()) {
						_pFirstNode = &newNode;
					} else {
						lastNode()->setNext(newNode);
					}

					_size++;
				}



public:				/// RETRIEVE NODE
	LinkedListNode<T_NODE>*	operator[](std::size_t position) const
				{
					LinkedListNode<T_NODE>*	pCurrentNode = _pFirstNode;

					if (position >= _size) {
						/// Try to detect this error in debug mode
						_DEBUG_TRAP();

						/// If trying to access non-existant node,
						/// point instead to last node instead.
						/// Its not an optimum solution.
						position = _size -1;
					}

					for (std::size_t i = position; i; i--) {
						pCurrentNode = pCurrentNode->getNext();
					}

					return pCurrentNode;
				}



public:				/// Check if linked list is empty
	bool			isEmpty(void) const
				{
					return (_pFirstNode == 0);
				}

				/// Get size of linked list
	std::size_t		size(void) const
				{
					return _size;
				}


private:
				/// Retrieve last node
	LinkedListNode<T_NODE>*	lastNode(void) const
				{
					if (isEmpty()) {
						return _pFirstNode;
					} else {
						return this->operator[](_size - 1);
					}
				}



private:			// PRIVATE VARIABLES
	LinkedListNode<T_NODE>*	_pFirstNode;	///< Pointer to first node, starts empty.
	std::size_t		_size;		///< Store size of linked list.
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__
