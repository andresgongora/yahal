// 1 TAB = 8 SPACES //

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/

#include "i2c_multimaster.hpp"
#include <msp430f5309.h>

/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DEFINITION::I2C_MASTER
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ==================================================================== CONSTRUCTOR & DESTRUCTOR**/
mcu::I2C_multimaster::I2C_multimaster(void)	{}
mcu::I2C_multimaster::~I2C_multimaster(void)	{}



/** ========================================================================= WRITE & READ & POLL**/
bool mcu::I2C_multimaster::writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
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



bool mcu::I2C_multimaster::write(uint8_t slaveAddress, uint8_t* data, std::size_t size)
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



bool mcu::I2C_multimaster::readRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, std::size_t size)
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



bool mcu::I2C_multimaster::read(uint8_t slaveAddress, uint8_t* data, std::size_t size)
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



bool mcu::I2C_multimaster::isSlavePresent(uint8_t slaveAddress)
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



/** ================================================================================= I2C EVENTS **/

void mcu::I2C_multimaster::handleReceivedStart(void)
{
	if(isMaster())	{}
	else		{I2C_slave::handleReceivedStart();}
}


void mcu::I2C_multimaster::handleReceivedStop(void)
{
	if(isMaster())	{}
	else		{I2C_slave::handleReceivedStop();}
}


void mcu::I2C_multimaster::handleReceivedNack(void)
{
	if(isMaster())	{I2C_master::handleReceivedNack();}
	else		{}
}

void mcu::I2C_multimaster::handleBufferTXEmpty(void)
{
	if(isMaster())	{I2C_master::handleBufferTXEmpty();}
	else		{I2C_slave::handleBufferTXEmpty();}
}


void mcu::I2C_multimaster::handleBufferRXFull(void)
{
	if(isMaster())	{I2C_master::handleBufferRXFull();}
	else		{I2C_slave::handleBufferRXFull();}
}


void mcu::I2C_multimaster::handleArbitrationLost(void)
{

}


/** ============================================================================================ **/
