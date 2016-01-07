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

#include "i2c_slave.hpp"



/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::I2C_slave::I2C_slave(void){}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::I2C_slave::handleReceivedStart(void)
{
	if(isIncommingWrite())	{_callbackStart.run(Direction::WRITE);}
	else			{_callbackStart.run(Direction::READ);}
}



void yahal::mcu::I2C_slave::handleReceivedStop(void)
{
	_callbackStop.run();
}



void yahal::mcu::I2C_slave::handleBufferTXEmpty(void)
{
	uint8_t byteToSend;	// If callback fails, set to 0xFF (default value)
	if(not _callbackByteRequested.run(byteToSend)){byteToSend = 0xFF;}

	// MASTER IS READING US -> Send next byte
	writeBufferTX(byteToSend);
}



void yahal::mcu::I2C_slave::handleBufferRXFull(void)
{
	volatile uint8_t receivedByte = readBufferRX();	// Read to free input buffer (if it exists)
	_callbackByteReceived.run(receivedByte);// Deliver byte to callback function
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::I2C_slave::setCallbackReceivedStart(void(*fpCallOnEvent)(Direction::Type))
{
	_callbackStart.setCallBackFunction(fpCallOnEvent);
}



void yahal::mcu::I2C_slave::setCallbackReceivedStop(void(*fpCallOnEvent)(void))
{
	_callbackStop.setCallBackFunction(fpCallOnEvent);
}



void yahal::mcu::I2C_slave::setCallbackByteReceived(void(*fpCallOnEvent)(uint8_t))
{
	_callbackByteReceived.setCallBackFunction(fpCallOnEvent);
}



void yahal::mcu::I2C_slave::setCallbackByteRequested(void(*fpCallOnEvent)(uint8_t&))
{
	_callbackByteRequested.setCallBackFunction(fpCallOnEvent);
}



/* ---------------------------------------------------------------------------------------------- */
