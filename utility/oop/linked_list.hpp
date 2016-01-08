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
	template <typename T> class LinkedList;
	template <typename T> class LinkedListNode;
}}}



/***********************************************************************************************//**
 * @brief	Linked list of templated type T_NODE.
 **************************************************************************************************/
template <typename T_NODE>
class yahal::utility::oop::LinkedList
{
public:				// CONSTRUCTOR
				LinkedList()	: _pFirstNode(0), _size(0)	{}


				/// APPEND NODE
	void			pushBack(T_NODE& newNode)
				{
					if (isEmpty()) {
						_pFirstNode = &newNode;
					} else {
						lastNode->setNext(newNode);
					}

					_size++;
				}



public:				/// RETRIEVE NODE
	T_NODE*			operator[](std::size_t possition) const
				{
					T_NODE*	pCurrentNode = _pFirstNode;

					if (possition >= _size) {
						_DEBUG_TRAP();

						/// If tryong to access non-existant node, point
						/// to last node instead.
						/// Its not an optimum solution.
						position = _size -1;
					}

					for (std::size_t i = possition; i; i--) {
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
	T_NODE*			lastNode(void) const
				{
					if (isEmpty()) {
						return _pFirstNode;
					} else {
						return this->operator[](_size - 1);
					}
				}



private:			// PRIVATE VARIABLES
	T_NODE*			_pFirstNode;	///< Pointer to first node, starts empty.
	std::size_t		_size;		///< Store size of linked list.
};





/***********************************************************************************************//**
 * @brief	Individual node of a linked list. Its type is T_NODE.
 **************************************************************************************************/
template <typename T_NODE>
class yahal::utility::oop::LinkedListNode
{
public:
				// CONSTRUCTOR
				LinkedListNode()		: _pNextNode(0)	{}


private:
				// FRIEND
	friend class		mcu::utility::LinkedList<T_NODE>;


				/// Set pointer to next node
	void			setNext(T_NODE& nextNode)	{_pNextNode = &nextNode;}


				/// Get pointer to next node
	T_NODE*			getNext(void) const		{return _pNextNode;}


				/// Pointer to next node of same class
	T_NODE*			_pNextNode;
};




/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_OOP_LINKED_LIST_HPP_INCLUDED__
