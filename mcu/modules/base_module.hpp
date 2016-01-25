// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015 - 2016, Individual contributors, see AUTHORS file 	|
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



#ifndef __YAHAL_MCU_MODULES_BASE_MODULE_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_BASE_MODULE_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "../../utility/oop/noncopyable.hpp"
#include "../../utility/oop/nonheapable.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{ namespace details{
	class BaseModule;
}}}}



/***********************************************************************************************//**
 * @brief	Base class for all MCU modules, it makes modules non-copiable and non-heapeable.
 **************************************************************************************************/
class yahal::mcu::modules::details::BaseModule :
	public yahal::utility::oop::NonCopyable,
	public yahal::utility::oop::NonHeapable
{
protected:
				BaseModule(void)	{}


public:
//	virtual bool		init(void) = 0;
};


/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_MCU_MODULES_BASE_MODULE_HPP_INCLUDED__
