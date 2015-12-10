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




	//TODO: Use a flag to enable TX and RX, and check if thos eare enabled when calling IRQ routines. User may call them by accident


#ifndef __MCU_I2C_MULTIMASTER_HPP_INCLUDED__
#define __MCU_I2C_MULTIMASTER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "i2c_master.hpp"
#include "i2c_slave.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	class I2C_multimaster;
}



/* ============================================================================================== */
 *	yahal::mcu::I2C_multimaster
 * ============================================================================================== */

class yahal::mcu::I2C_multimaster : public yahal::mcu::I2C_master, public yahal::mcu::I2C_slave
{
protected:			// CONTRUSTOR & DESTRUCTOR
				I2C_multimaster(void);
	virtual			~I2C_multimaster(void);


protected:			// I2C PROTOCOL -> IMPLEMENT
	virtual bool		isMaster(void) = 0;
	virtual void		configureAsMaster(void) = 0;



	void			setMasterCallbacks(void);
	void			setSlaveCallbacks(void);


public:				// WRITE & READ & POLL
	bool virtual 		writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size);
	bool virtual		write(uint8_t slaveAddress, uint8_t* data, std::size_t size);
	bool virtual		readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size);
	bool virtual		read(uint8_t slaveAddress, uint8_t* data, std::size_t size);
	bool virtual		isSlavePresent(uint8_t slaveAddress);



//protected:			// I2C EVENTS -> TO BE USED BY IMPLEMENTATION (ISR)
	void			handleArbitrationLost(void);
	void			handleReceivedStart(void);
	void			handleReceivedStop(void);
	void			handleReceivedNack(void);
	void			handleBufferTXEmpty(void);
	void			handleBufferRXFull(void);



/*
private:
	void			handleMasterReceivedNack(void);
	void			handleMasterBufferTXEmpty(void);
	void			handleMasterBufferRXFull(void);
	void			handleSlaveReceivedStart(void);
	void			handleSlaveReceivedStop(void);
	void			handleSlaveBufferTXEmpty(void);
	void			handleSlaveBufferRXFull(void);






private:			// EVENT CALLBACKS
	yahal::mcu::utility::Callback<yahal::mcu::I2C_multimaster,void> _callbackHandleReceivedStart;
	yahal::mcu::utility::Callback<yahal::mcu::I2C_multimaster,void> _callbackHandleReceivedStop;
	yahal::mcu::utility::Callback<yahal::mcu::I2C_multimaster,void> _callbackHandleReceivedNack;
	yahal::mcu::utility::Callback<yahal::mcu::I2C_multimaster,void> _callbackHandleBufferTXEmpty;
	yahal::mcu::utility::Callback<yahal::mcu::I2C_multimaster,void> _callbackHandleBufferRXFull;*/
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __MCU_I2C_MULTIMASTER_HPP_INCLUDED__
