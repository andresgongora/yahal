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

#ifndef __YAHAL_UTILITY_DATA_MASK_HPP_INCLUDED__
#define __YAHAL_UTILITY_DATA_MASK_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace utility{ namespace data{
	template<typename T> T setMasked(T variable, T new_value, T mask);
	template<typename T> void setBits(volatile T& variable, T mask);
	template<typename T> void unsetBits(volatile T& variable, T mask);
}}}



/***********************************************************************************************//**
 *
 **************************************************************************************************/
template<typename T> T yahal::utility::data::setMasked(T variable, T new_value, T mask)
{
	T and_mask = (~mask) | new_value;
	T or_mask  =   mask  & new_value;

	return ((variable & and_mask) | or_mask);
}



/***********************************************************************************************//**
 *
 **************************************************************************************************/
template<typename T> void setBits(volatile T& variable, T mask)
{
	variable |= mask;
}

template<typename T> void unsetBits(volatile T& variable, T mask)
{
	variable &= ~mask;
}


/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_UTILITY_DATA_MASK_HPP_INCLUDED__
