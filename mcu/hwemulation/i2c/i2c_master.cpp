// 1 TAB = 8 SPACES //

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



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "i2c_master.hpp"
#ifdef __MCU_HWEMULATION_I2C_MASTER_ENABLED__



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DEFINITION::M430F2132_I2C_MASTER
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ============================================================================= INITIALIZATION **/

bool mcu::hwemulation::I2C_master::init()
{
	emulateReset();
	this->setInitialized();
	return true;
}


mcu::hwemulation::I2C_master::I2C_master(Gpio::Port::Pin sda, Gpio::Port::Pin scl) :
	_sda(sda),
	_scl(scl),
	_sendStart(false),
	_sendStop(false),
	_bufferTXStatus(BUFFER_STATUS::EMPTY),
	_bufferRXStatus(BUFFER_STATUS::EMPTY),
	_receivedNack(false)
{}



/** ======================================================================================== PIN **/

void mcu::hwemulation::I2C_master::setSDA(bool b)
{
	if(b)
	{
		_sda.config(Gpio::DIRECTION::INPUT);
	}
	else
	{
		_sda.set(0);
		_sda.config(Gpio::DIRECTION::OUTPUT);
	}
}


bool mcu::hwemulation::I2C_master::getSDA(void)
{
	_sda.config(Gpio::DIRECTION::INPUT);
	return _sda.get();
}



void mcu::hwemulation::I2C_master::setSCL(bool b)
{
	if(b)
	{
		_scl.config(Gpio::DIRECTION::INPUT);
	}
	else
	{
		_scl.set(0);
		_scl.config(Gpio::DIRECTION::OUTPUT);
	}
}


bool mcu::hwemulation::I2C_master::getSCL(void)
{
	_scl.config(Gpio::DIRECTION::INPUT);
	return _scl.get();
}


/** ======================================================================================== BIT **/


void mcu::hwemulation::I2C_master::sendBit(bool b)
{
	setSCL(0);
	setSDA(b);
	while(getSCL() == 0){}		// Release CLK and wait if slave pulls SCL down
	setSCL(0);
}


bool mcu::hwemulation::I2C_master::receiveBit(void)
{
	bool b;

	setSCL(0);
	setSDA(1);			// Release SDA
	while(getSCL() == 0){}		// Release CLK and wait if slave pulls SCL down
	b = getSDA();
	setSCL(0);

	return b;
}


/** ======================================================================================= BYTE **/

void mcu::hwemulation::I2C_master::sendByte(uint8_t byte)
{
	for(int8_t i=7; i>=0; i--)
	{
		bool b = (byte>>i) & 0x01;
		sendBit(b);
	}
}



uint8_t mcu::hwemulation::I2C_master::receiveByte(void)
{
	uint8_t byte = 0;
	bool b;

	for(int8_t i=7; i>=0; i--)
	{
		b = receiveBit();
		byte |= (b<<i);
	}

	return byte;
}

/** =============================================================================== I2C PROTOCOL **/

void mcu::hwemulation::I2C_master::sendStart(void)
{
	setSCL(1);			//		________
	setSDA(1);			//	SDA		\_______________
	setSDA(0);			//		________________
	setSCL(0);			//	SCL			\_______
}


void mcu::hwemulation::I2C_master::sendStop(void)
{
	setSCL(0);			//				________
	setSDA(0);			//	SDA	_______________/
	setSCL(1);			//			________________
	setSDA(1);			//	SCL	_______/
}


void mcu::hwemulation::I2C_master::sendAck(void)
{
	sendBit(0);
}


void mcu::hwemulation::I2C_master::sendNack(void)
{
	sendBit(1);
}


bool mcu::hwemulation::I2C_master::receiveAck(void)
{
	return receiveBit();
}



/** =============================================================================== EMULATED I2C **/

void mcu::hwemulation::I2C_master::emulateStart(void)
{
	bool 	readBit 	=  _direction == DIRECTION::READ ? true : false;
	uint8_t composedAddress	= (_slaveAddress << 1) + readBit;


	sendStart();				// Send start sequence
	sendByte(composedAddress);		// Send address
	bool nack = receiveAck();		// Get: NACK = 1; ACK = 0;


	if(nack)
	{
		_receivedNack = true;		// NACK IRQ
		_direction = DIRECTION::WRITE;	// IF READING, ABORT IT: This is needed so that in the emulaiton loop a STOP is sent as soon as possible
	}
	else if(_direction == DIRECTION::WRITE )
	{
		_bufferTXStatus = BUFFER_STATUS::JUST_READ;	// TX IRQ
	}
}

void mcu::hwemulation::I2C_master::emulateStop(void)
{
	sendStop();
}

//--------------------------------------------------------------------------------------------------

void mcu::hwemulation::I2C_master::emulateIRQTX(void)
{
	this->handleBufferTXEmpty();			//Call parent method signaling IRQ

}

void mcu::hwemulation::I2C_master::emulateIRQRX(void)
{
	this->handleBufferRXFull();		//Call parent method signaling IRQ
}

void mcu::hwemulation::I2C_master::emulateIRQNack(void)
{
	this->handleReceivedNack();		//Call parent method signaling IRQ
}

//--------------------------------------------------------------------------------------------------

void mcu::hwemulation::I2C_master::emulateWriteBufferTX(uint8_t byte)
{
	_bufferTX = byte;			// Write to buffer
	_bufferTXStatus = BUFFER_STATUS::JUST_WRITTEN;
}

void mcu::hwemulation::I2C_master::emulateSendBufferTX(void)
{
	sendByte(_bufferTX);
	bool nack = receiveAck();		// NACK = 1; ACK = 0;
	if(nack){_receivedNack = true;}
}

//--------------------------------------------------------------------------------------------------

void mcu::hwemulation::I2C_master::emulateReceiveBufferRX(void)
{
	uint8_t byte = receiveByte();

	// RESPOND
	if(_sendStop)				// Stop reading -> NACK + STOP
	{
		sendNack();
		_direction = DIRECTION::WRITE;
	}
	else					// Continue reading -> ACK
	{
		sendAck();
	}


	// WRITE BUFFER
	_bufferRX = byte;
	_bufferRXStatus = BUFFER_STATUS::JUST_WRITTEN;
}

uint8_t	mcu::hwemulation::I2C_master::emulateReadBufferRX(void)
{
	uint8_t byte = _bufferRX;		// Read buffer to auxiliar variable
	_bufferRXStatus = BUFFER_STATUS::EMPTY;
	return byte;				// Return copied content of buffer
}

//--------------------------------------------------------------------------------------------------

void mcu::hwemulation::I2C_master::emulateLoop(void)
{
	// While no STOP is sent, keep emulating HW features
	bool busy = true;

	while(busy)
	{
		// NACK IRQ
		if(_receivedNack)
		{
			_receivedNack = false;
			emulateIRQNack();
		}

		// RX IRQ
		else if(_bufferRXStatus == BUFFER_STATUS::JUST_WRITTEN)
		{
			_bufferRXStatus = BUFFER_STATUS::FULL;
			emulateIRQRX();
		}

		// TX IRQ
		else if(_bufferTXStatus == BUFFER_STATUS::JUST_READ)
		{
			_bufferTXStatus = BUFFER_STATUS::EMPTY;
			emulateIRQTX();
		}

		// STOP
		else if(_sendStop && _direction == DIRECTION::WRITE)
		{
			_sendStop = false;
			emulateStop();
			busy = false;
		}

		// START
		else if(_sendStart)
		{
			busy = true;
			_sendStart = false;
			emulateStart();
		}

		// READ
		else if(_direction == DIRECTION::READ)
		{
			emulateReceiveBufferRX();
		}

		// WRITE
		else if(_bufferTXStatus == BUFFER_STATUS::JUST_WRITTEN)
		{
			emulateSendBufferTX();
			_bufferTXStatus = BUFFER_STATUS::JUST_READ;
		}

		// DEFAULT: STOP
		else
		{
			_sendStop = false;
			emulateStop();
			busy = false;
		}
	}

	// CLEAR ALL JUST TO BE ON THE SAFE SIDE
	emulateReset();

}

void mcu::hwemulation::I2C_master::emulateReset(void)
{
	_sendStart = false;
	_sendStop = false;
	_bufferTXStatus = BUFFER_STATUS::EMPTY;
	_bufferTXStatus = BUFFER_STATUS::EMPTY;
	_receivedNack = false;
	_direction = DIRECTION::WRITE;
}



/** ====================================================================== MODULE IMPLEMENTATION **/

void mcu::hwemulation::I2C_master::start(uint8_t slaveAddress, DIRECTION::type direction)
{
	_direction = direction;
	_slaveAddress = slaveAddress;
	_sendStart = true;
}


void mcu::hwemulation::I2C_master::stop(void)
{
	_sendStop = true;			// Request STOP sequence ASAP
}


void mcu::hwemulation::I2C_master::acknowledge(bool ack)
{

}


void mcu::hwemulation::I2C_master::writeBufferTX(uint8_t byte)
{
	emulateWriteBufferTX(byte);
}


uint8_t	mcu::hwemulation::I2C_master::readBufferRX(void)
{
	return emulateReadBufferRX();
}


void mcu::hwemulation::I2C_master::awaitTransmissionEnd(void)
{
	emulateLoop();
}




/** ============================================================================================ **/
#endif // __SOFTWARE_I2C_MASTER_ENABLED__
