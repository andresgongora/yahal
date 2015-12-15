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

bool yahal::mcu::I2C_master::writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	this->open();

	_slaveAddress 		= slaveAddress;
	_registerAddress	= registerAddress;
	_sendRegisterAddress 	= true;
	_numTransmissions	= size;
	_pBuffer		= data;
	_direction 		= Direction::WRITE;

	bool success = transmit();
	this->close();
	return success;
}


bool yahal::mcu::I2C_master::write(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	this->open();

	_slaveAddress 		= slaveAddress;
	_registerAddress	= 0x00;
	_sendRegisterAddress 	= false;
	_numTransmissions	= size;
	_pBuffer		= data;
	_direction 		= Direction::WRITE;

	bool success = transmit();
	this->close();
	return success;
}


/** ======================================================================================= READ **/

bool yahal::mcu::I2C_master::readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	this->open();

	_slaveAddress 		= slaveAddress;
	_registerAddress	= registerAddress;
	_sendRegisterAddress 	= true;
	_numTransmissions	= size;
	_pBuffer		= data;
	_direction 		= Direction::READ;

	bool success = transmit();
	this->close();
	return success;
}


bool yahal::mcu::I2C_master::read(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	this->open();

	_slaveAddress 		= slaveAddress;
	_registerAddress	= 0x00;
	_sendRegisterAddress 	= false;
	_numTransmissions	= size;
	_pBuffer		= data;
	_direction 		= Direction::READ;

	bool success = transmit();
	this->close();
	return success;
}


/** ==================================================================================== UTILITY **/


bool yahal::mcu::I2C_master::isSlavePresent(uint8_t slaveAddress)
{
	uint8_t dummy;
	write(slaveAddress, &dummy, 0);		/* This is the least invasive way to poll a slave.
						   It will send a START and inmediately a STOP,
						   taking note only of ACK or NACK	*/
	return not hasError(); 			// Returns true if no error occurred -> ACK received
}


/** ======================================================================================== IRQ **/

void yahal::mcu::I2C_master::handleBufferTXEmpty(void)
{
	// This fuction might be entered because
	// - Need to send register address, regardless if it is Write or Read 	-> Send RegAddr
	// - This is a Read and the register address has just been sent 	-> Restart
	// - This is a Write and there is data to be sent			-> Send data
	// - All data has been sent (last byte just went out)			-> Stop

	if(_sendRegisterAddressPending)
	{
		_sendRegisterAddressPending = false;
		writeBufferTX(_registerAddress);
	}
	else if(_direction == Direction::READ)
	{
		sendStart(); //restart
	}
	else if(pendingTransmissions())
	{
		// STORE DATA IN CASE ANOTHER IRQ HAPPENS
		uint8_t currentTransmission = _numTransmitted;
		_numTransmitted++;

		// SEND DATA
		writeBufferTX(_pBuffer[currentTransmission]);
	}
	else // Nothing left to be done
	{
		stop();
	}
}



void yahal::mcu::I2C_master::handleBufferRXFull(void)
{
	// STORE DATA IN CASE ANOTHER IRQ HAPPENS
	uint8_t currentTransmission = _numTransmitted;
	_numTransmitted++;

	// PREPRARE TO RECEIVE LAST BYTE
	if(pendingTransmissions() == 1) // Last byte is waiting in the shift register
	{
		stop(); // Send stop as soon as the last byte enters the RX buffer
	}

	volatile uint8_t receivedByte = readBufferRX();	// Free RX buffer


	if(currentTransmission >= _numTransmissions)
	{
		setErrorCode(Error::READ_OVERFLOW_ATTEMPT);
	}
	else
	{
		_pBuffer[currentTransmission] = receivedByte;
	}
}



void yahal::mcu::I2C_master::handleReceivedNack(void)
{
	if(pendingTransmissions() == _numTransmissions)
		{setErrorCode(Error::SLAVE_NOT_REACHABLE);}

	else
		{setErrorCode(Error::SLAVE_DATA_NACK);}

	stop();	// Either case, stop transmission
}



/** =============================================================================== TRANSMISSION **/

bool yahal::mcu::I2C_master::transmit(void)
{
	// CHECK FOR ERRORS
	if     (_slaveAddress & 0x80)			{setErrorCode(Error::SLAVE_ADDRESS_NOT_7_BIT);}
	else if(_numTransmissions>0 && _pBuffer == 0)	{setErrorCode(Error::INVALID_MESSAGE_BUFFER);}
//	else if(_numTransmissions==0)			{setErrorCode(Error::ZERO_SIZE_MESSAGE);}


	else // TRANSMISSION HAS NO ERRORS
	{
		_numTransmitted = 0;
		_sendRegisterAddressPending = _sendRegisterAddress;


		sendStart();
		awaitTransmissionEnd();


		// CHECK FOR ERRORS OCCURRED DURING TRANSMISSION
		if(this->hasError())			{} // Avoid overwriting error code
		else if(pendingTransmissions() > 0)	{setErrorCode(Error::TRANSMISSION_PREMATURELY_ENDED);}
	}


	return not hasError(); // Returns true if no error occurred
}


void yahal::mcu::I2C_master::sendStart(void)
{
	// READ WITHOUT PREVIOUS WRITE
	if(_direction == Direction::READ && not _sendRegisterAddressPending)
	{
		start(_slaveAddress, Direction::READ);		// Sends START and starts receiving first byte
		if(pendingTransmissions() <= 1) {stop();} 	// Stop inmediately after first byte received
	}

	// WRITE OR READ WITH REGISTER ADDREESS
	else
	{
		start(_slaveAddress, Direction::WRITE);
	}
}



std::size_t yahal::mcu::I2C_master::pendingTransmissions(void)
{
	return _numTransmissions - _numTransmitted;
}





/* ---------------------------------------------------------------------------------------------- */

