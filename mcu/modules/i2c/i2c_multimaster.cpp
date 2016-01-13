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

#include "i2c_multimaster.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::modules::I2C_multimaster::I2C_multimaster(void)	{}



/* ---------------------------------------------------------------------------------------------- */
bool yahal::mcu::modules::I2C_multimaster::writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2C_master::writeRegister(slaveAddress, registerAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2C_multimaster::write(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2C_master::write(slaveAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2C_multimaster::readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2C_master::readRegister(slaveAddress, registerAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2C_multimaster::read(uint8_t slaveAddress, uint8_t* data, std::size_t size)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2C_master::read(slaveAddress, data, size);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



bool yahal::mcu::modules::I2C_multimaster::isSlavePresent(uint8_t slaveAddress)
{
	bool arbitrationLost = true;
	bool success = false;

	while(arbitrationLost)
	{
		configureAsMaster();

		success = I2C_master::isSlavePresent(slaveAddress);
		if(success || isMaster()){arbitrationLost = false;}
	}

	return success;
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::modules::I2C_multimaster::handleReceivedStart(void)
{
	if(isMaster())	{}
	else		{I2C_slave::handleReceivedStart();}
}


void yahal::mcu::modules::I2C_multimaster::handleReceivedStop(void)
{
	if(isMaster())	{}
	else		{I2C_slave::handleReceivedStop();}
}


void yahal::mcu::modules::I2C_multimaster::handleReceivedNack(void)
{
	if(isMaster())	{I2C_master::handleReceivedNack();}
	else		{}
}

void yahal::mcu::modules::I2C_multimaster::handleBufferTXEmpty(void)
{
	if(isMaster())	{I2C_master::handleBufferTXEmpty();}
	else		{I2C_slave::handleBufferTXEmpty();}
}


void yahal::mcu::modules::I2C_multimaster::handleBufferRXFull(void)
{
	if(isMaster())	{I2C_master::handleBufferRXFull();}
	else		{I2C_slave::handleBufferRXFull();}
}


void yahal::mcu::modules::I2C_multimaster::handleArbitrationLost(void)
{

}


/* ---------------------------------------------------------------------------------------------- */
