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




/* ---------------------------------------------------------------------------------------------- */
#include <mcu/modules/uart/uart.hpp>


/* ============================================================================================== */
 *	DEFINITION::UART
 * ============================================================================================== */

/** ====================================================================================== WRITE **/

bool HAL::MCU::Uart::write(uint8_t* data, uint8_t len)
{
	// CHECK IF INITIALIZED
	if(!isInitialized())
	{
		setErrorCode(error_notInitialized);
		return false;
	}


	#ifndef _UART_USE_BLOCKING_TX
	while(isTXEnabled());	// Wait for previous TX to end
	#endif


	setErrorCode(noError);


	// PREPARE STACK
	if(!stackTX.prepareNew(len, MESSAGESTACK_OUTGOING))
	{
		setErrorCode(error_unableToInitTXMessage);
		return false;
	}
	if(!stackTX.loadFrom(data))
	{
		setErrorCode(error_unableToInitTXMessage);
		return false;
	}

	enableTX();
	isrTX();

	#ifdef _UART_USE_BLOCKING_TX
	while(isTXEnabled());	// Wait for current TX to end
	#endif
	return true;
}


bool HAL::MCU::Uart::write(char* data, uint8_t len)		{return write((uint8_t*)data,len);}
bool HAL::MCU::Uart::write(const char* data, uint8_t len)	{return write((uint8_t*)data,len);}
bool HAL::MCU::Uart::write(const char* data)			{return write((uint8_t*)data,std::strlen(data));}
bool HAL::MCU::Uart::write(uint8_t &data)			{return write(&data,1);}
bool HAL::MCU::Uart::write(char &data)				{return write((uint8_t*)&data,1);}
bool HAL::MCU::Uart::write(std::string& str)			{return write((uint8_t*)str.data(), str.size());}


/** ======================================================================================= READ **/

bool HAL::MCU::Uart::read(uint8_t* data, uint8_t len)
{
	// CHECK IF INITIALIZED
	if(!isInitialized())
	{
		setErrorCode(error_notInitialized);
		return false;
	}
	clearErrorCode();


	// PREPARE STACK
	if(!stackRX.prepareNew(len, MESSAGESTACK_INCOMMING))
	{
		setErrorCode(error_unableToInitRXMessage);
		return false;
	}


	enableRX();


	while(isRXEnabled());
	if(!stackRX.unloadTo(data)) return false;
	return true;
}


bool HAL::MCU::Uart::read(char* data, uint8_t len)	{return read((uint8_t*)data,len);}
bool HAL::MCU::Uart::read(uint8_t &data)		{return read(&data,1);}
bool HAL::MCU::Uart::read(char &data)			{return read((uint8_t*)&data,1);}


uint8_t HAL::MCU::Uart::read()
{
	uint8_t aux;
	if(read(&aux,1))	return aux;
	else			return 0;
}

/** ======================================================================================== ISR **/

void HAL::MCU::Uart::isrTX(void)
{
	if(!isTXEnabled())	return;


	if(stackTX.isTransmissionDone())
	{
		disableTX();
		return;
	}


	sendByte(stackTX.retrieveNextByte());
}


void HAL::MCU::Uart::isrRX(void)
{
	if(!isRXEnabled())	return;


	// EMPTY RX BUFFER
	uint8_t inByte = receiveByte();


	// IF RX-IRQ AND NO DATA EXPECTED -> CALL AUTOMATIC RX FUNCTION
	if(isCallOnRXEnabled() && stackRX.isTransmissionDone())
	{
		callOnRX(inByte);
		return;
	}


	// NORMAL READ
	stackRX.appendNextByte(inByte);
	if(stackRX.isTransmissionDone())
	{
		if(!isCallOnRXEnabled())	disableRX();
		return;
	}
}



/** =============================================================================== AUTOMATIC RX **/

void HAL::MCU::Uart::enableCallOnRX(void (* functionRX)(uint8_t))
{
	functionRX_ = functionRX;
	if(functionRX != 0)	enableRX();
}


void HAL::MCU::Uart::disableCallOnRX(void)
{
	functionRX_ = 0;
	if(stackRX.isTransmissionDone()) disableRX();	// No read in progress
}


bool HAL::MCU::Uart::isCallOnRXEnabled(void) const
{
	return(functionRX_);
}


void HAL::MCU::Uart::callOnRX(uint8_t byteRX)
{
	// CHECK FOR VALID POINTER AND CALL IT
	if(isCallOnRXEnabled())
	{
		(*functionRX_)(byteRX);
	}
	else
	{
		setErrorCode(error_attemptToCallDisabledCallOnRXFunction);
	}
}



/** ======================================================================= TRANSMISSION CONTROL **/

void HAL::MCU::Uart::enableTX(void)
{
	enableTXIRQ();
	flagTXEnabled = true;

}


void HAL::MCU::Uart::enableRX(void)
{
	enableRXIRQ();
	flagRXEnabled = true;
}


void HAL::MCU::Uart::disableTX(void)
{
	flagTXEnabled = false;
	disableTXIRQ();

}


void HAL::MCU::Uart::disableRX(void)
{
	flagRXEnabled = false;
	disableRXIRQ();
}


bool HAL::MCU::Uart::isTXEnabled(void)	const	{return flagTXEnabled;}
bool HAL::MCU::Uart::isRXEnabled(void)	const	{return flagRXEnabled;}


/* ---------------------------------------------------------------------------------------------- */

