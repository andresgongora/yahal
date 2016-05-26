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

#include "ads1115.hpp"



/* ---------------------------------------------------------------------------------------------- */

yahal::sensors::adc::Ads1115::Ads1115(yahal::mcu::modules::I2CMaster& i2c) :
	i2c_(i2c)
{}

/* ---------------------------------------------------------------------------------------------- */

void yahal::sensors::adc::Ads1115::setDataRate(uint8_t data_rate)
{
	Register config;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
	config.low &= 0b00011111;
	config.low |= ((data_rate & 0x07) << 5);
	i2c_.writeRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
}


void yahal::sensors::adc::Ads1115::setScale(uint8_t full_scale)
{
	Register config;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
	config.high &= 0b11110001;
	config.high |= ((full_scale & 0x07) << 1);
	i2c_.writeRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
}


void yahal::sensors::adc::Ads1115::setChannel(uint8_t channel)
{
	Register config;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
	config.high &= 0b10001111;
	config.high |= ((channel & 0x07) << 4);
	i2c_.writeRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
}


void yahal::sensors::adc::Ads1115::setContinuousConversion(bool b)
{
	Register config;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
	if(b)	{config.high &= 0b11111110;}
	else	{config.high |= 0b00000001;}
	i2c_.writeRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
}

/* ---------------------------------------------------------------------------------------------- */

int16_t yahal::sensors::adc::Ads1115::getData(void)
{
	Register rawData;
	uint16_t data;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONVERSION, (uint8_t*)&rawData, sizeof(rawData));
	data = rawData.low + (rawData.high << 8);
	return data;
}

/* ---------------------------------------------------------------------------------------------- */

yahal::sensors::adc::Ads1115::DataRate::Type yahal::sensors::adc::Ads1115::getDataRate(void) const
{
	Register config;
	DataRate::Type data_rate;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
	data_rate = static_cast<DataRate::Type>((config.low & 0b11100000) >> 5);
	return data_rate;
}


yahal::sensors::adc::Ads1115::Scale::Type yahal::sensors::adc::Ads1115::getScale(void) const
{
	Register config;
	Scale::Type scale;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
	scale = static_cast<Scale::Type>((config.high & 0b00001110) >> 1);
	return scale;
}


yahal::sensors::adc::Ads1115::Channel::Type yahal::sensors::adc::Ads1115::getChannel(void) const
{
	Register config;
	Channel::Type channel;

	i2c_.readRegister(ADDRESS, RegisterAddress::CONFIG, (uint8_t*)&config, sizeof(config));
	channel = static_cast<Channel::Type>((config.high & 0b01110000) >> 4);
	return channel;
}

/* ---------------------------------------------------------------------------------------------- */
