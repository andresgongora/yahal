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



#ifndef __MCU_HWEMULATION_I2C_MASTER_HPP_INCLUDED__
#define __MCU_HWEMULATION_I2C_MASTER_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "../hwemulation_config.hpp"
#ifdef __MCU_HWEMULATION_I2C_MASTER_ENABLED__

#include <stdint.h>
#include "../../modules/i2c/i2c_master.hpp"
#include "../../modules/gpio/gpio.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{ namespace hwemulation{
	class I2C_master;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION::I2C_MASTER
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::hwemulation::I2C_master : public mcu::I2C_master
{
public:
				// CONSTRUCTOR -----------------------------------------------------
				I2C_master(Gpio::Port::Pin sda, Gpio::Port::Pin scl);


				// INITIALIZATION
	bool			init(void);


private:			// MODULE IMPLEMENTATION -------------------------------------------
	void			start(uint8_t slaveAddress, DIRECTION::type direction);
	void			stop(void);
	void			acknowledge(bool ack);
	void			writeBufferTX(uint8_t byte);
	uint8_t			readBufferRX(void);
	void			awaitTransmissionEnd(void);



private:			// PIN -------------------------------------------------------------
	void			setSDA(bool b);
	bool			getSDA(void);
	void			setSCL(bool b);
	bool			getSCL(void);



				// BIT -------------------------------------------------------------
	void			sendBit(bool b);
	bool			receiveBit(void);



				// BYTE ------------------------------------------------------------
	void			sendByte(uint8_t byte);
	uint8_t			receiveByte(void);



				// I2C PROTOCOL ----------------------------------------------------
	void			sendStart(void);
	void			sendStop(void);
	void			sendAck(void);
	void			sendNack(void);
	bool			receiveAck(void);



				// CONTROL ---------------------------------------------------------
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



				// PIN
	Gpio::Port::Pin 	_sda;
	Gpio::Port::Pin		_scl;


				struct BUFFER_STATUS{ enum type{
					FULL,
					EMPTY,
					JUST_WRITTEN,
					JUST_READ,
				};};



				// HW EMULATION
	uint8_t			_slaveAddress;
	DIRECTION::type		_direction;
	uint8_t 		_bufferTX;
	uint8_t			_bufferRX;
	bool			_sendStart;
	bool			_sendStop;
	BUFFER_STATUS::type	_bufferTXStatus;
	BUFFER_STATUS::type	_bufferRXStatus;
	bool			_receivedNack;
};


/** ============================================================================================ **/
#endif // __MCU_HWEMULATION_I2C_MASTER_ENABLED__
#endif // __MCU_HWEMULATION_I2C_MASTER_HPP_INCLUDED__
