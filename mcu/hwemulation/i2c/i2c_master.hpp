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

#ifndef __YAHAL_MCU_HWEMULATION_I2C_MASTER_HPP_INCLUDED__
#define __YAHAL_MCU_HWEMULATION_I2C_MASTER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include "../../modules/i2c/i2c_master.hpp"
#include "../../modules/gpio/gpio.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace hwemulation{
	class I2CMaster;
}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::hwemulation::I2CMaster : public yahal::mcu::modules::I2CMaster
{
public:
	 	 	 	struct Configuration
				{
	 	 	 		yahal::mcu::modules::Gpio::Port::Pin* const sda;	///< Data.
	 	 	 		yahal::mcu::modules::Gpio::Port::Pin* const scl;	///< Clock.
	 	 	 	};


				// CONSTRUCTOR
				I2CMaster(const Configuration& configuration);


				// INITIALIZATION
	virtual void		doInit(void);


private:			// MODULE IMPLEMENTATION
	void			start(uint8_t slave_address, Direction::Type direction);
	void			stop(void);
	void			acknowledge(bool ack);
	void			writeBufferTX(uint8_t byte);
	uint8_t			readBufferRX(void);
	void			awaitTransmissionEnd(void);



private:			// PIN
	void			setSDA(bool b);
	bool			getSDA(void);
	void			setSCL(bool b);
	bool			getSCL(void);



				// BIT
	void			sendBit(bool b);
	bool			receiveBit(void);



				// BYTE
	void			sendByte(uint8_t byte);
	uint8_t			receiveByte(void);



				// I2C PROTOCOL
	void			sendStart(void);
	void			sendStop(void);
	void			sendAck(void);
	void			sendNack(void);
	bool			receiveAck(void);



				// CONTROL
	void			emulateStart(void);
	void			emulateStop(void);
	void			emulateIRQTX(void);
	void			emulateIRQRX(void);
	void			emulateIRQNack(void);
	void			emulateWriteBufferTX(uint8_t byte);
	void			emulateSendBufferTX(void);
	void			emulateReceiveBufferRX(void);
	uint8_t			emulateReadBufferRX(void);
	void			emulateLoop(void);
	void			emulateReset(void);


				struct BufferStatus{ enum Type{
					FULL,
					EMPTY,
					JUST_WRITTEN,
					JUST_READ,
				};};



				// Private variables
	const Configuration&	configuration_;
	uint8_t			slave_address_;
	Direction::Type		direction_;
	uint8_t 		buffer_TX_;
	uint8_t			buffer_RX_;
	bool			end_start_;
	bool			send_stop_;
	BufferStatus::Type	buffer_TX_status_;
	BufferStatus::Type	buffer_RX_status_;
	bool			received_nack_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // __YAHAL_MCU_HWEMULATION_I2C_MASTER_HPP_INCLUDED__
