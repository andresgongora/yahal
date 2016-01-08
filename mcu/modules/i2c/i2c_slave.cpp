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
yahal::mcu::I2C_slave::I2C_slave(void) :
	_pExternalHandler(NULL)
{}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::I2C_slave::setExternalHandler(ExternalHandler* pExternalHandler)
{
	_pExternalHandler = pExternalHandler;
}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::I2C_slave::handleReceivedStart(void)
{
	if (_pExternalHandler) {
		if (isIncommingWrite()) {
			_pExternalHandler->notifyStart(Direction::WRITE);
		} else {
			_pExternalHandler->notifyStart(Direction::READ);
		}
	}
}



void yahal::mcu::I2C_slave::handleReceivedStop(void)
{
	if (_pExternalHandler) {
		_pExternalHandler->notifyStop();
	}
}



void yahal::mcu::I2C_slave::handleBufferTXEmpty(void)
{
	uint8_t byteToSend = 0xFF;	///< Default value 0xFF

	if (_pExternalHandler) {
		byteToSend = _pExternalHandler->requestTXByte();
	}

	writeBufferTX(byteToSend);	///< MASTER IS READING US -> Send next byte
}



void yahal::mcu::I2C_slave::handleBufferRXFull(void)
{
	volatile uint8_t receivedByte = readBufferRX();	///< Read buffer in order to free it for next transmission

	if (_pExternalHandler) {
		_pExternalHandler->deliverRXByte(receivedByte);
	}
}



/* ---------------------------------------------------------------------------------------------- */
