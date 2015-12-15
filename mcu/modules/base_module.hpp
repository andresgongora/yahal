// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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



#ifndef __YAHAL_MCU_GENERIC_MODULE_HPP_INCLUDED__
#define __YAHAL_MCU_GENERIC_MODULE_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "../../utility/oop/noncopyable.hpp"
#include "../../error/error_code.hpp"
#include "../rtos/rtos.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace detail{
	class BaseModule;
}}}



/***********************************************************************************************//**
 * Base class for all MCU modules.
 * This class implements all methods that are common to all modules.
 * It also inherits from noncopyable, prohibiting the copy of any class, as they are asociated
 * to physical resources.
 **************************************************************************************************/
class yahal::mcu::detail::BaseModule :
	public yahal::error::ErrorCode,
	private yahal::utility::oop::Noncopyable
{
protected:
				BaseModule(void)	{}
	virtual			~BaseModule(void)	{}



public:
				/**
				 * Public initialization method.
				 * It calls doInit.
				 * @see doInit()
				 */
	bool			init(void){
					this->setErrorCode(NO_ERROR);
					doInit();
					return not this->hasError();
				}



protected:
				/** Prepare module for exclusive operation */
	void			open(void){
					_mutex.lock();
					this->setErrorCode(NO_ERROR);
					if(not isInitialized()){init();}	// Try to init
				}

				/** Releases module */
	void			close(void){
					_mutex.unlock();
				}

				/** Must be implemented by each module */
	virtual void		doInit(void) = 0;



private:
	yahal::mcu::rtos::Mutex	_mutex;	/**< Mutex for exclusive access to each derived module */
};


/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_MCU_GENERIC_MODULE_HPP_INCLUDED__
