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

#include "i2c_slave.hpp"



/* ---------------------------------------------------------------------------------------------- */
yahal::mcu::modules::I2CSlave::I2CSlave(void) :
	p_event_handler_(NULL)
{}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::modules::I2CSlave::setEventHandler(EventHandler* p_event_handler)
{
	p_event_handler_ = p_event_handler;
}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::modules::I2CSlave::handleReceivedStart(void)
{
	if (p_event_handler_) {
		if (isIncommingWrite()) {
			p_event_handler_->handleStart(Direction::WRITE);
		} else {
			p_event_handler_->handleStart(Direction::READ);
		}
	}
}



void yahal::mcu::modules::I2CSlave::handleReceivedStop(void)
{
	if (p_event_handler_) {
		p_event_handler_->handleStop();
	}
}



void yahal::mcu::modules::I2CSlave::handleBufferTXEmpty(void)
{
	uint8_t byteToSend = 0xFF;	///< Default value 0xFF

	if (p_event_handler_) {
		byteToSend = p_event_handler_->handleTXByte();
	}

	writeBufferTX(byteToSend);	///< MASTER IS READING US -> Send next byte
}



void yahal::mcu::modules::I2CSlave::handleBufferRXFull(void)
{
	volatile uint8_t receivedByte = readBufferRX();	///< Read buffer in order to free it for next transmission

	if (p_event_handler_) {
		p_event_handler_->handleRXByte(receivedByte);
	}
}



/* ---------------------------------------------------------------------------------------------- */
