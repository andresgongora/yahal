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



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "ads1115.hpp"


/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::sensors::Ads1115
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

hal::sensors::Ads1115::Ads1115(mcu::I2C_master& i2c) :
	_i2c(i2c),
	ADDRESS(0x48),
	_fullScale(SCALE::FS_2048_MV)
{}



void hal::sensors::Ads1115::setDataRate(DATA_RATE::type dataRate)
{
	Register config;
	_i2c.readRegister(ADDRESS, 1, (uint8_t*)&config, sizeof(config));
	config.low &= 0b00011111;
	config.low |= (dataRate << 5);
	_i2c.writeRegister(ADDRESS, REGISTER_ADDRESS::CONFIG, (uint8_t*)&config, sizeof(config));
}



void hal::sensors::Ads1115::setScale(SCALE::type fullScale)
{
	Register config;
	_i2c.readRegister(ADDRESS, REGISTER_ADDRESS::CONFIG, (uint8_t*)&config, sizeof(config));
	config.high &= 0b11110001;
	config.high |= (fullScale << 1);
	_i2c.writeRegister(ADDRESS, REGISTER_ADDRESS::CONFIG, (uint8_t*)&config, sizeof(config));
	_fullScale = fullScale;
}


void hal::sensors::Ads1115::setInput(INPUT::type input)
{
	Register config;
	_i2c.readRegister(ADDRESS, REGISTER_ADDRESS::CONFIG, (uint8_t*)&config, sizeof(config));
	config.high &= 0b10001111;
	config.high |= (input << 4);
	_i2c.writeRegister(ADDRESS, REGISTER_ADDRESS::CONFIG, (uint8_t*)&config, sizeof(config));

	volatile unsigned long int i;
	for(i=10000; i>0; i--);
}


void hal::sensors::Ads1115::setContinuousConversion(bool b)
{
	Register config;
	_i2c.readRegister(ADDRESS, REGISTER_ADDRESS::CONFIG, (uint8_t*)&config, sizeof(config));
	if(b)	{config.high &= 0b11111110;}
	else	{config.high |= 0b00000001;}
	_i2c.writeRegister(ADDRESS, REGISTER_ADDRESS::CONFIG, (uint8_t*)&config, sizeof(config));
}


int16_t hal::sensors::Ads1115::getData(void)
{
	Register rawData;
	uint16_t data;
	_i2c.readRegister(ADDRESS, REGISTER_ADDRESS::CONVERSION, (uint8_t*)&rawData, sizeof(rawData));
	data = rawData.low + (rawData.high << 8);
	return data;
}


/** ============================================================================================ **/
