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





#ifndef __YAHAL_MCU_I2C_SLAVE_HPP_INCLUDED__
#define __YAHAL_MCU_I2C_SLAVE_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "i2c_common.hpp"
#include "../../../utility/oop/callback.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	class I2C_slave;
}}



/***********************************************************************************************//**
 * @brief	Base class for all I2C slaves
 **************************************************************************************************/
class yahal::mcu::I2C_slave : virtual public yahal::mcu::details::I2C_common
{
protected:			// CONSTRUCTOR & DESTRUCTOR
				I2C_slave(void);
	virtual			~I2C_slave(void);



protected:			// I2C PROTOCOL -> IMPLEMENT
	virtual bool		isIncommingWrite(void) = 0;


public:
//protected:			// I2C EVENTS -> TO BE USED BY IMPLEMENTATION (ISR)
	virtual void		handleReceivedStart(void);
	virtual void		handleReceivedStop(void);
	virtual void		handleBufferTXEmpty(void);
	virtual void		handleBufferRXFull(void);



public:				// SET CALLBACK FUNCTIONS FOR HOOKS
	void			setCallbackReceivedStart(void(*fpCallOnEvent)(Direction::Type));
	void			setCallbackReceivedStop(void(*fpCallOnEvent)(void));
	void			setCallbackByteReceived(void(*fpCallOnEvent)(uint8_t));
	void			setCallbackByteRequested(void(*fpCallOnEvent)(uint8_t&));



private:			// PRIVATE VARIABLES
	yahal::utility::oop::Callback<Direction::Type>	_callbackStart;
	yahal::utility::oop::Callback<void>		_callbackStop;
	yahal::utility::oop::Callback<uint8_t>		_callbackByteReceived;
	yahal::utility::oop::Callback<uint8_t&>		_callbackByteRequested;
};


/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_MCU_I2C_SLAVE_HPP_INCLUDED__
