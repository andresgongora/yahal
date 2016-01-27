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

#ifndef __YAHAL_MCU_MODULES_I2C_SLAVE_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_I2C_SLAVE_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "i2c_common.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{
	class I2CSlave;
}}}



/***********************************************************************************************//**
 * @brief	Base class for all I2C slaves
 *
 *
 **************************************************************************************************/
class yahal::mcu::modules::I2CSlave : virtual public yahal::mcu::modules::details::I2CCommon
{
protected:			/// This is a base class.
				I2CSlave(void) {}

public:
				/// This class allows derived classes to be notified of slave events.
				class EventHandler
				{
				protected:
							EventHandler(void) {}

				public:
					virtual void	handleStart(Direction::Type)= 0;/// Signal a start has been received
					virtual void	handleStop(void) = 0; 		/// Signal a stop has been received
					virtual void	handleRXByte(uint8_t) = 0; 	/// Delivers received byte to handler
					virtual uint8_t	handleTXByte(void) = 0; 	/// Request next byte to be sent to handler

					virtual		~EventHandler(void) {}
				};

				// -----------------------------------------------------------------

				/// Set pointer to class that will handle all slave events.
	virtual void		setEventHandler(EventHandler* const p_event_handler) = 0;
};


/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_MCU_MODULES_I2C_SLAVE_HPP_INCLUDED__
