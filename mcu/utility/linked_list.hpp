// 1 TAB = 8 SPACES //

      /**
	*	ID:	linked_list.hpp
	*   EDITED:	06-05-2015
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|	Abstract HAL class for digital LINKED_LIST 					|
	*	|										|
	*	|	PINS:	Range:	0 - 7 (bit index)					|
	*	|	PORTS:	Range:	1 - Hardware Max (implementation dependant)		|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/


#ifndef __MCU_LINKED_LIST_HPP_INCLUDED__
#define __MCU_LINKED_LIST_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <cstdlib>


/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace utility
{
	template <typename T> class LinkedList;
	template <typename T> class LinkedListNode;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	utility::LinkedList
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/
template <typename T_NODE>
class mcu::utility::LinkedList
{
public:				// CONSTRUCTOR & DESTRUCTOR
				LinkedList()	: _pFirstNode(0), _size(0)	{}


				// APPEND NODE
	void			pushBack(T_NODE& newNode)
				{
					if(isEmpty())	{_pFirstNode = & newNode;}
					else		{lastNode->setNext(newNode);}

					_size++;
				}



public:				// RETRIEVE NODE
	T_NODE*			operator[](std::size_t possition) const
				{
					T_NODE*	pCurrentNode = _pFirstNode;

					if(possition >= _size)
					{
						for(;;); //WARNING TODO ERROR!!!!!
					}
					else
					{
						for(std::size_t i = possition; i; i--)
						{
							pCurrentNode = pCurrentNode->getNext();
						}
					}

					return pCurrentNode;
				}



public:				// UTILITY
	bool			isEmpty(void) const
				{
					return (_pFirstNode == 0);
				}

	std::size_t		size(void) const
				{
					return _size;
				}

private:T_NODE*			lastNode(void) const
				{
					if(isEmpty())	{return 0}
					else 		{return this->operator[](_size-1);}
				}



private:			// PRIVATE VARIABLES
	T_NODE*			_pFirstNode;
	std::size_t		_size;
};



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	utility::LinkedListNode
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/
template <typename T_NODE>
class mcu::utility::LinkedListNode
{
public:
				// CONSTRUCTOR & DESTRUCTOR
				LinkedListNode()		: _pNextNode(0)	{}
	virtual			~LinkedListNode()				{}


private:
				// FRIEND
	friend class		mcu::utility::LinkedList<T_NODE>;


				// PRIVATE ACCESSOR
	void			setNext(T_NODE& nextNode)	{_pNextNode = &nextNode;}
	T_NODE*			getNext(void) const		{return _pNextNode;}


				// PRIVATE VARIABLES
	T_NODE*			_pNextNode;
};




/** ============================================================================================ **/
#endif 	// __MCU_LINKED_LIST_HPP_INCLUDED__
