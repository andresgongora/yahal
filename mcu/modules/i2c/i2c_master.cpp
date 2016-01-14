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




#include "i2c_master.hpp"

/* ============================================================================================== */

/** ====================================================================================== WRITE **/

bool yahal::mcu::modules::I2CMaster::writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	this->open();

	slave_address_ 		= slaveAddress;
	register_address_	= registerAddress;
	send_register_address_ 	= true;
	num_transmissions_	= size;
	p_buffer_		= data;
	direction_ 		= Direction::WRITE;

	bool success = transmit();
	this->close();
	return success;
}


bool yahal::mcu::modules::I2CMaster::write(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	this->open();

	slave_address_ 		= slaveAddress;
	register_address_	= 0x00;
	send_register_address_ 	= false;
	num_transmissions_	= size;
	p_buffer_		= data;
	direction_ 		= Direction::WRITE;

	bool success = transmit();
	this->close();
	return success;
}


/** ======================================================================================= READ **/

bool yahal::mcu::modules::I2CMaster::readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	this->open();

	slave_address_ 		= slaveAddress;
	register_address_	= registerAddress;
	send_register_address_ 	= true;
	num_transmissions_	= size;
	p_buffer_		= data;
	direction_ 		= Direction::READ;

	bool success = transmit();
	this->close();
	return success;
}


bool yahal::mcu::modules::I2CMaster::read(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	this->open();

	slave_address_ 		= slaveAddress;
	register_address_	= 0x00;
	send_register_address_ 	= false;
	num_transmissions_	= size;
	p_buffer_		= data;
	direction_ 		= Direction::READ;

	bool success = transmit();
	this->close();
	return success;
}


/** ==================================================================================== UTILITY **/


bool yahal::mcu::modules::I2CMaster::isSlavePresent(uint8_t slaveAddress)
{
	uint8_t dummy;
	write(slaveAddress, &dummy, 0);		/* This is the least invasive way to poll a slave.
						   It will send a START and inmediately a STOP,
						   taking note only of ACK or NACK	*/
	return not hasError(); 			// Returns true if no error occurred -> ACK received
}


/** ======================================================================================== IRQ **/

void yahal::mcu::modules::I2CMaster::handleBufferTXEmpty(void)
{
	// This fuction might be entered because
	// - Need to send register address, regardless if it is Write or Read 	-> Send RegAddr
	// - This is a Read and the register address has just been sent 	-> Restart
	// - This is a Write and there is data to be sent			-> Send data
	// - All data has been sent (last byte just went out)			-> Stop

	if(send_register_address_pending_)
	{
		send_register_address_pending_ = false;
		writeBufferTX(register_address_);
	}
	else if(direction_ == Direction::READ)
	{
		sendStart(); //restart
	}
	else if(pendingTransmissions())
	{
		// STORE DATA IN CASE ANOTHER IRQ HAPPENS
		uint8_t currentTransmission = num_transmitted_;
		num_transmitted_++;

		// SEND DATA
		writeBufferTX(p_buffer_[currentTransmission]);
	}
	else // Nothing left to be done
	{
		stop();
	}
}



void yahal::mcu::modules::I2CMaster::handleBufferRXFull(void)
{
	// STORE DATA IN CASE ANOTHER IRQ HAPPENS
	uint8_t currentTransmission = num_transmitted_;
	num_transmitted_++;

	// PREPRARE TO RECEIVE LAST BYTE
	if(pendingTransmissions() == 1) // Last byte is waiting in the shift register
	{
		stop(); // Send stop as soon as the last byte enters the RX buffer
	}

	volatile uint8_t receivedByte = readBufferRX();	// Free RX buffer


	if(currentTransmission >= num_transmissions_)
	{
		setErrorCode(Error::READ_OVERFLOW_ATTEMPT);
	}
	else
	{
		p_buffer_[currentTransmission] = receivedByte;
	}
}



void yahal::mcu::modules::I2CMaster::handleReceivedNack(void)
{
	if(pendingTransmissions() == num_transmissions_)
		{setErrorCode(Error::SLAVE_NOT_REACHABLE);}

	else
		{setErrorCode(Error::SLAVE_DATA_NACK);}

	stop();	// Either case, stop transmission
}



/** =============================================================================== TRANSMISSION **/

bool yahal::mcu::modules::I2CMaster::transmit(void)
{
	// CHECK FOR ERRORS
	if     (slave_address_ & 0x80)			{setErrorCode(Error::SLAVE_ADDRESS_NOT_7_BIT);}
	else if(num_transmissions_>0 && p_buffer_ == 0)	{setErrorCode(Error::INVALID_MESSAGE_BUFFER);}
//	else if(num_transmissions_==0)			{setErrorCode(Error::ZERO_SIZE_MESSAGE);} ///< I now use 0 size messages to ping a slave


	else // TRANSMISSION HAS NO ERRORS
	{
		num_transmitted_ = 0;
		send_register_address_pending_ = send_register_address_;	///< Flag is address TX is pending. Because we just started we copy the configuration value.


		sendStart();
		awaitTransmissionEnd();


		// CHECK FOR ERRORS OCCURRED DURING TRANSMISSION
		if(this->hasError())			{} // Avoid overwriting error code
		else if(pendingTransmissions() > 0)	{setErrorCode(Error::TRANSMISSION_PREMATURELY_ENDED);}
	}


	return not hasError(); // Returns true if no error occurred
}


void yahal::mcu::modules::I2CMaster::sendStart(void)
{
	// READ WITHOUT PREVIOUS WRITE
	if(direction_ == Direction::READ && not send_register_address_pending_)
	{
		start(slave_address_, Direction::READ);		// Sends START and starts receiving first byte
		if(pendingTransmissions() <= 1) {stop();} 	// Stop inmediately after first byte received
	}

	// WRITE OR READ WITH REGISTER ADDREESS
	else
	{
		start(slave_address_, Direction::WRITE);
	}
}



std::size_t yahal::mcu::modules::I2CMaster::pendingTransmissions(void)
{
	return num_transmissions_ - num_transmitted_;
}





/* ---------------------------------------------------------------------------------------------- */

