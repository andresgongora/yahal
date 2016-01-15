// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015 - 2016 - 2016, Individual contributors, see AUTHORS file. |
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

#ifndef __YAHAL_MCU_MODULES_OUTPUT_COMPARE_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_OUTPUT_COMPARE_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "../base_module.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{
	class OutputCompare;
}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::modules::OutputCompare : public yahal::mcu::modules::details::BaseModule
{
public:
				struct Error{ enum Type{
					NO_ERROR = NO_ERROR_CODE,
					MODE_NOT_AVAILABLE,
					OTHER
				};};


				struct Mode{ enum Type{
					OUTPUT,
					SET,
					RESET,
					TOGGLE,
					TOGGLE_SET,
					TOGGLE_RESET,
					SET_RESET,
					RESET_SET,
				};};




protected:
				OutputCompare(void){}


public:
	virtual std::size_t	getWidth(void) const = 0;
	virtual std::size_t	getMaxCount(void) const = 0;

	virtual bool		hasMode(Mode::Type mode) const = 0;
	virtual bool		setMode(Mode::Type mode) = 0;

	virtual void		resetCounter(std::size_t value) = 0;
	virtual void		setComparator(std::size_t value) = 0;
	virtual std::size_t	getCounter(void) const = 0;
//	virtual std::size_t	getComparator(void) const = 0;
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_OUTPUT_COMPARE_HPP_INCLUDED__
