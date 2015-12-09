// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*    AUTOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|										|
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


#ifndef __MCU_I2C_SLAVE_HPP_INCLUDED__
#define __MCU_I2C_SLAVE_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <stdint.h>
#include <cstddef>
#include "i2c_common.hpp"
#include "../../utility/callback.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{
	class I2C_slave;
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION::I2C
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/


class mcu::I2C_slave : virtual public mcu::I2C_common
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
	void			setCallbackReceivedStart(void(*fpCallOnEvent)(DIRECTION::type));
	void			setCallbackReceivedStop(void(*fpCallOnEvent)(void));
	void			setCallbackByteReceived(void(*fpCallOnEvent)(uint8_t));
	void			setCallbackByteRequested(void(*fpCallOnEvent)(uint8_t&));



private:			// PRIVATE VARIABLES
	mcu::utility::Callback<DIRECTION::type> _callbackStart;
	mcu::utility::Callback<void>		_callbackStop;
	mcu::utility::Callback<uint8_t>		_callbackByteReceived;
	mcu::utility::Callback<uint8_t&>	_callbackByteRequested;
};


/** ============================================================================================ **/
#endif 	// __MCU_I2C_SLAVE_HPP_INCLUDED__
