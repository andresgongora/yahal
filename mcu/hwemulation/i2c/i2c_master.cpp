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

#include "i2c_master.hpp"


/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::hwemulation::I2CMaster::I2CMaster(const Configuration& configuration) :
	configuration_(configuration),
	end_start_(false),
	send_stop_(false),
	buffer_TX_status_(BufferStatus::EMPTY),
	buffer_RX_status_(BufferStatus::EMPTY),
	received_nack_(false)
{}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::hwemulation::I2CMaster::doInit()
{
	emulateReset();
}






/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::hwemulation::I2CMaster::setSDA(bool b)
{
	if(b)
	{
		configuration_.sda->config(yahal::mcu::modules::Gpio::Direction::INPUT);
	}
	else
	{
		configuration_.sda->set(0);
		configuration_.sda->config(yahal::mcu::modules::Gpio::Direction::OUTPUT);
	}
}


bool yahal::mcu::hwemulation::I2CMaster::getSDA(void)
{
	configuration_.sda->config(yahal::mcu::modules::Gpio::Direction::INPUT);
	return configuration_.sda->get();
}



void yahal::mcu::hwemulation::I2CMaster::setSCL(bool b)
{
	if(b)
	{
		configuration_.scl->config(yahal::mcu::modules::Gpio::Direction::INPUT);
	}
	else
	{
		configuration_.scl->set(0);
		configuration_.scl->config(yahal::mcu::modules::Gpio::Direction::OUTPUT);
	}
}


bool yahal::mcu::hwemulation::I2CMaster::getSCL(void)
{
	configuration_.scl->config(yahal::mcu::modules::Gpio::Direction::INPUT);
	return configuration_.scl->get();
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::hwemulation::I2CMaster::sendBit(bool b)
{
	setSCL(0);
	setSDA(b);
	while(getSCL() == 0){}		// Release CLK and wait if slave pulls SCL down
	setSCL(0);
}


bool yahal::mcu::hwemulation::I2CMaster::receiveBit(void)
{
	bool b;

	setSCL(0);
	setSDA(1);			// Release SDA
	while(getSCL() == 0){}		// Release CLK and wait if slave pulls SCL down
	b = getSDA();
	setSCL(0);

	return b;
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::hwemulation::I2CMaster::sendByte(uint8_t byte)
{
	for(int8_t i=7; i>=0; i--)
	{
		bool b = (byte>>i) & 0x01;
		sendBit(b);
	}
}



uint8_t yahal::mcu::hwemulation::I2CMaster::receiveByte(void)
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



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::hwemulation::I2CMaster::sendStart(void)
{
	setSCL(1);			//		________
	setSDA(1);			//	SDA		\_______________
	setSDA(0);			//		________________
	setSCL(0);			//	SCL			\_______
}


void yahal::mcu::hwemulation::I2CMaster::sendStop(void)
{
	setSCL(0);			//				________
	setSDA(0);			//	SDA	_______________/
	setSCL(1);			//			________________
	setSDA(1);			//	SCL	_______/
}


void yahal::mcu::hwemulation::I2CMaster::sendAck(void)
{
	sendBit(0);
}


void yahal::mcu::hwemulation::I2CMaster::sendNack(void)
{
	sendBit(1);
}


bool yahal::mcu::hwemulation::I2CMaster::receiveAck(void)
{
	return receiveBit();
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::hwemulation::I2CMaster::emulateStart(void)
{
	bool 	readBit 	=  direction_ == Direction::READ ? true : false;
	uint8_t composedAddress	= (slave_address_ << 1) + readBit;


	sendStart();				// Send start sequence
	sendByte(composedAddress);		// Send address
	bool nack = receiveAck();		// Get: NACK = 1; ACK = 0;


	if(nack)
	{
		received_nack_ = true;		// NACK IRQ
		direction_ = Direction::WRITE;	// IF READING, ABORT IT: This is needed so that in the emulaiton loop a STOP is sent as soon as possible
	}
	else if(direction_ == Direction::WRITE )
	{
		buffer_TX_status_ = BufferStatus::JUST_READ;	// TX IRQ
	}
}

void yahal::mcu::hwemulation::I2CMaster::emulateStop(void)
{
	sendStop();
}



//--------------------------------------------------------------------------------------------------

void yahal::mcu::hwemulation::I2CMaster::emulateIRQTX(void)
{
	this->handleBufferTXEmpty();			//Call parent method signaling IRQ

}

void yahal::mcu::hwemulation::I2CMaster::emulateIRQRX(void)
{
	this->handleBufferRXFull();		//Call parent method signaling IRQ
}

void yahal::mcu::hwemulation::I2CMaster::emulateIRQNack(void)
{
	this->handleReceivedNack();		//Call parent method signaling IRQ
}



//--------------------------------------------------------------------------------------------------

void yahal::mcu::hwemulation::I2CMaster::emulateWriteBufferTX(uint8_t byte)
{
	buffer_TX_ = byte;			// Write to buffer
	buffer_TX_status_ = BufferStatus::JUST_WRITTEN;
}

void yahal::mcu::hwemulation::I2CMaster::emulateSendBufferTX(void)
{
	sendByte(buffer_TX_);
	bool nack = receiveAck();		// NACK = 1; ACK = 0;
	if(nack){received_nack_ = true;}
}



//--------------------------------------------------------------------------------------------------

void yahal::mcu::hwemulation::I2CMaster::emulateReceiveBufferRX(void)
{
	uint8_t byte = receiveByte();

	// RESPOND
	if(send_stop_)				// Stop reading -> NACK + STOP
	{
		sendNack();
		direction_ = Direction::WRITE;
	}
	else					// Continue reading -> ACK
	{
		sendAck();
	}


	// WRITE BUFFER
	buffer_RX_ = byte;
	buffer_RX_status_ = BufferStatus::JUST_WRITTEN;
}

uint8_t	yahal::mcu::hwemulation::I2CMaster::emulateReadBufferRX(void)
{
	uint8_t byte = buffer_RX_;		// Read buffer to auxiliar variable
	buffer_RX_status_ = BufferStatus::EMPTY;
	return byte;				// Return copied content of buffer
}



//--------------------------------------------------------------------------------------------------

void yahal::mcu::hwemulation::I2CMaster::emulateLoop(void)
{
	// While no STOP is sent, keep emulating HW features
	bool busy = true;

	while(busy)
	{
		// NACK IRQ
		if(received_nack_)
		{
			received_nack_ = false;
			emulateIRQNack();
		}

		// RX IRQ
		else if(buffer_RX_status_ == BufferStatus::JUST_WRITTEN)
		{
			buffer_RX_status_ = BufferStatus::FULL;
			emulateIRQRX();
		}

		// TX IRQ
		else if(buffer_TX_status_ == BufferStatus::JUST_READ)
		{
			buffer_TX_status_ = BufferStatus::EMPTY;
			emulateIRQTX();
		}

		// STOP
		else if(send_stop_ && direction_ == Direction::WRITE)
		{
			send_stop_ = false;
			emulateStop();
			busy = false;
		}

		// START
		else if(end_start_)
		{
			busy = true;
			end_start_ = false;
			emulateStart();
		}

		// READ
		else if(direction_ == Direction::READ)
		{
			emulateReceiveBufferRX();
		}

		// WRITE
		else if(buffer_TX_status_ == BufferStatus::JUST_WRITTEN)
		{
			emulateSendBufferTX();
			buffer_TX_status_ = BufferStatus::JUST_READ;
		}

		// DEFAULT: STOP
		else
		{
			send_stop_ = false;
			emulateStop();
			busy = false;
		}
	}

	// CLEAR ALL JUST TO BE ON THE SAFE SIDE
	emulateReset();

}

void yahal::mcu::hwemulation::I2CMaster::emulateReset(void)
{
	end_start_ = false;
	send_stop_ = false;
	buffer_TX_status_ = BufferStatus::EMPTY;
	buffer_TX_status_ = BufferStatus::EMPTY;
	received_nack_ = false;
	direction_ = Direction::WRITE;
}



/** ====================================================================== MODULE IMPLEMENTATION **/

void yahal::mcu::hwemulation::I2CMaster::start(uint8_t slave_address, Direction::Type direction)
{
	direction_ = direction;
	slave_address_ = slave_address;
	end_start_ = true;
}


void yahal::mcu::hwemulation::I2CMaster::stop(void)
{
	send_stop_ = true;			// Request STOP sequence ASAP
}


void yahal::mcu::hwemulation::I2CMaster::acknowledge(bool ack)
{

}


void yahal::mcu::hwemulation::I2CMaster::writeBufferTX(uint8_t byte)
{
	emulateWriteBufferTX(byte);
}


uint8_t	yahal::mcu::hwemulation::I2CMaster::readBufferRX(void)
{
	return emulateReadBufferRX();
}


void yahal::mcu::hwemulation::I2CMaster::awaitTransmissionEnd(void)
{
	emulateLoop();
}




/* ---------------------------------------------------------------------------------------------- */
