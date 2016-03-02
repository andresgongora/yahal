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

#ifndef __YAHAL_SENSORS_ADC_ADS1115_HPP_INCLUDED__
#define __YAHAL_SENSORS_ADC_ADS1115_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include "../../../mcu/modules/i2c/i2c_master.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace sensors{ namespace adc{
	class Ads1115;
}}}



/***********************************************************************************************//**
 * @brief	ADS1115 analog to digital converter
 **************************************************************************************************/
class yahal::sensors::adc::Ads1115
{
public:
				struct DataRate{ enum Type{
					SPS_8 	= 0b000,
					SPS_16	= 0b001,
					SPS_32	= 0b010,
					SPS_64	= 0b011,
					SPS_128	= 0b100,
					SPS_250	= 0b101,
					SPS_475	= 0b110,
					SPS_860	= 0b111
				};} static const DATA_RATE;

				struct Scale{ enum Type{
					FS_6144_MV	= 0b000,
					FS_4096_MV	= 0b001,
					FS_2048_MV	= 0b010,
					FS_1024_MV	= 0b011,
					FS_512_MV	= 0b100,
					FS_256_MV	= 0b111
				};} static const SCALE;

				struct Channel{ enum Type{
					AIN0_AIN1	= 0b000,
					AIN0_AIN3	= 0b001,
					AIN1_AIN3	= 0b010,
					AIN2_AIN3	= 0b011,
					AIN0_GND	= 0b100,
					AIN1_GND	= 0b101,
					AIN2_GND	= 0b110,
					AIN3_GND	= 0b111
				};} static const CHANNEL;

				// -----------------------------------------------------------------

				Ads1115(yahal::mcu::modules::I2CMaster& i2c);

	void			setDataRate(uint8_t data_rate);
	void			setScale(uint8_t full_scale);
	void			setChannel(uint8_t channel);
	void			setContinuousConversion(bool b=true);

	int16_t			getData(void);
/*	float			getVoltage(void)
				{
					int16_t rawData;
					float voltage;
					float scale;

					switch(_fullScale)
					{
					case SCALE::FS_6144_MV:	scale = 6.144f / 32768; break;
					case SCALE::FS_4096_MV:	scale = 4.096f / 32768; break;
					case SCALE::FS_1024_MV:	scale = 1.024f / 32768; break;
					case SCALE::FS_512_MV:	scale = 0.512f / 32768; break;
					case SCALE::FS_256_MV:	scale = 0.256f / 32768; break;
					default:
					case SCALE::FS_2048_MV:	scale = 2.048f / 32768; break;
					}


					rawData = getData();
					voltage = rawData * scale;
					return voltage;
				}
	float			getVoltage(Channel::Type channel)
				{
					setChannel(channel);
					return getVoltage();
				}
*/

				// -----------------------------------------------------------------
private:
				struct RegisterAddress{ enum Type{
					CONVERSION 	= 0b00,
					CONFIG 		= 0b01,
					LO_THRESH	= 0b10,
					HI_THRESH	= 0b11
				};};

				struct Register
				{
					uint8_t high;
					uint8_t low;
				};

				// -----------------------------------------------------------------

	DataRate::Type		getDataRate(void) const;
	Scale::Type		getScale(void) const;
	Channel::Type		getChannel(void) const;

	yahal::mcu::modules::I2CMaster& 	i2c_;
	const uint8_t				ADDRESS = 0x48;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // __YAHAL_SENSORS_ADC_ADS1115_HPP_INCLUDED__
