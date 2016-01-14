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

#include "i2c_multimaster.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::modules::I2CMultimaster::I2CMultimaster(void)	{}



/* ---------------------------------------------------------------------------------------------- */
bool yahal::mcu::modules::I2CMultimaster::writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMaster::writeRegister(slaveAddress, registerAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimaster::write(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMaster::write(slaveAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimaster::readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMaster::readRegister(slaveAddress, registerAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimaster::read(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMaster::read(slaveAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimaster::isSlavePresent(uint8_t slaveAddress)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMaster::isSlavePresent(slaveAddress);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::modules::I2CMultimaster::handleReceivedStart(void)
{
	if(isMaster())	{}
	else		{I2CSlave::handleReceivedStart();}
}


void yahal::mcu::modules::I2CMultimaster::handleReceivedStop(void)
{
	if(isMaster())	{}
	else		{I2CSlave::handleReceivedStop();}
}


void yahal::mcu::modules::I2CMultimaster::handleReceivedNack(void)
{
	if(isMaster())	{I2CMaster::handleReceivedNack();}
	else		{}
}

void yahal::mcu::modules::I2CMultimaster::handleBufferTXEmpty(void)
{
	if(isMaster())	{I2CMaster::handleBufferTXEmpty();}
	else		{I2CSlave::handleBufferTXEmpty();}
}


void yahal::mcu::modules::I2CMultimaster::handleBufferRXFull(void)
{
	if(isMaster())	{I2CMaster::handleBufferRXFull();}
	else		{I2CSlave::handleBufferRXFull();}
}


void yahal::mcu::modules::I2CMultimaster::handleArbitrationLost(void)
{

}


/* ---------------------------------------------------------------------------------------------- */
