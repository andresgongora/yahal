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





#ifndef __YAHAL_MCU_MODULES_I2C_MASTER_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_I2C_MASTER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <cstddef>
#include "i2c_common.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace modules{
	class I2CMaster;
}}}



/***********************************************************************************************//**
 * @brief	Base class for all I2C Masters
 **************************************************************************************************/
class yahal::mcu::modules::I2CMaster : virtual public yahal::mcu::modules::details::I2CCommon
{
protected:			// CONSTRUCTOR & DESTRUCTOR
				I2CMaster(void)	{}



protected:			// I2C PROTOCOL -> IMPLEMENT

				/**
				 * @brief	Start I/O with slave.
				 * @param	slaveAddress address to perform I/O on.
				 * @param	direction Direction::READ or Direction::Write.
				 */
	virtual void		start(uint8_t slaveAddress, Direction::Type direction) = 0;

				/**
				 * @brief	Send stop.
				 */
	virtual void		stop(void) = 0;

				/**
				 * @brief	Wait (or block) while I/O in progress.
				 * You should check for error codes after the code returns from
				 * this function to assert a correct transmission.
				 */
	virtual void		awaitTransmissionEnd(void) = 0;



public:				// WRITE & READ & POLL
	virtual bool 		writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size);
	virtual bool 		write(uint8_t slaveAddress, uint8_t* data, std::size_t size);
	virtual bool 		readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size);
	virtual bool		read(uint8_t slaveAddress, uint8_t* data, std::size_t size);
	virtual bool 		isSlavePresent(uint8_t slaveAddress);



public:				// FAST WRITE & READ TEMPLATES
	template <typename T>
	bool 			writeRegister(uint8_t slaveAddr, uint8_t regAddr, T& data){
					return writeRegister(slaveAddr, regAddr, (uint8_t*)&data, sizeof(T));
				}

	template <typename T>
	bool 			write(uint8_t slaveAddr, T& data){
					return write(slaveAddr, (uint8_t*)&data, sizeof(T));
				}

	template <typename T>
	bool 			readRegister(uint8_t slaveAddr, uint8_t regAddr, T& data){
					return readRegister(slaveAddr, regAddr, (uint8_t*)&data, sizeof(T));
				}

	template <typename T>
	bool 			read(uint8_t slaveAddr, T& data){
					return read(slaveAddr, (uint8_t*)&data, sizeof(T));
				}



protected:			// I2C EVENTS -> TO BE USED BY IMPLEMENTATION (ISR)
	virtual void		handleBufferTXEmpty(void);
	virtual void		handleBufferRXFull(void);
	virtual void		handleReceivedNack(void);



private:			// PRIVATE CONTROL METHODS
	bool			transmit(void);			// Perform IO
	void			sendStart(void);
	std::size_t		pendingTransmissions(void);	// Get num of pending transmissions



private:			// PRIVATE VARIABLES
	uint8_t			slave_address_;
	uint8_t			register_address_;
	bool			send_register_address_;
	std::size_t		num_transmissions_;
	uint8_t*		p_buffer_;
	Direction::Type		direction_;

	volatile std::size_t	num_transmitted_;		// Might be changed by ISR
	volatile bool		send_register_address_pending_;	// Might be changed by ISR
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	// __YAHAL_MCU_MODULES_I2C_MASTER_HPP_INCLUDED__
