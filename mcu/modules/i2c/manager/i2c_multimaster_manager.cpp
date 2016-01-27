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

#include "i2c_multimaster_manager.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::modules::I2CMultimasterManager::I2CMultimasterManager(void)	{}



/* ---------------------------------------------------------------------------------------------- */
bool yahal::mcu::modules::I2CMultimasterManager::writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMasterManager::writeRegister(slaveAddress, registerAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimasterManager::write(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMasterManager::write(slaveAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimasterManager::readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMasterManager::readRegister(slaveAddress, registerAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimasterManager::read(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMasterManager::read(slaveAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2CMultimasterManager::isSlavePresent(uint8_t slaveAddress)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2CMasterManager::isSlavePresent(slaveAddress);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



void yahal::mcu::modules::I2CMultimasterManager::setEventHandler(EventHandler* const p_event_handler)
{
	I2CSlaveManager::setEventHandler(p_event_handler);
}


/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::modules::I2CMultimasterManager::handleReceivedStart(void)
{
	if(isMaster())	{}
	else		{I2CSlaveManager::handleReceivedStart();}
}


void yahal::mcu::modules::I2CMultimasterManager::handleReceivedStop(void)
{
	if(isMaster())	{}
	else		{I2CSlaveManager::handleReceivedStop();}
}


void yahal::mcu::modules::I2CMultimasterManager::handleReceivedNack(void)
{
	if(isMaster())	{I2CMasterManager::handleReceivedNack();}
	else		{}
}

void yahal::mcu::modules::I2CMultimasterManager::handleBufferTXEmpty(void)
{
	if(isMaster())	{I2CMasterManager::handleBufferTXEmpty();}
	else		{I2CSlaveManager::handleBufferTXEmpty();}
}


void yahal::mcu::modules::I2CMultimasterManager::handleBufferRXFull(void)
{
	if(isMaster())	{I2CMasterManager::handleBufferRXFull();}
	else		{I2CSlaveManager::handleBufferRXFull();}
}


void yahal::mcu::modules::I2CMultimasterManager::handleArbitrationLost(void)
{

}


/* ---------------------------------------------------------------------------------------------- */
