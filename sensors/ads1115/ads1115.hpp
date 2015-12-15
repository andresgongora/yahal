// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*   AUTHOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|										|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

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

#ifndef __ADS1115_HPP_INCLUDED__
#define __ADS1115_HPP_INCLUDED__



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <stdint.h>
#include "../../mcu/modules/i2c/i2c_master.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace hal{ namespace sensors{
	class Ads1115;
}}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	GPIO
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/
class hal::sensors::Ads1115
{
public:
				struct DATA_RATE{ enum type{
					SPS_8 	= 0b000,
					SPS_16	= 0b001,
					SPS_32	= 0b010,
					SPS_64	= 0b011,
					SPS_128	= 0b100,
					SPS_250	= 0b101,
					SPS_475	= 0b110,
					SPS_860	= 0b111
				};};

				struct SCALE{ enum type{
					FS_6144_MV	= 0b000,
					FS_4096_MV	= 0b001,
					FS_2048_MV	= 0b010,
					FS_1024_MV	= 0b011,
					FS_512_MV	= 0b100,
					FS_256_MV	= 0b111
				};};

				struct INPUT{ enum type{
					AIN0_AIN1	= 0b000,
					AIN0_AIN3	= 0b001,
					AIN1_AIN3	= 0b010,
					AIN2_AIN3	= 0b011,
					AIN0_GND	= 0b100,
					AIN1_GND	= 0b101,
					AIN2_GND	= 0b110,
					AIN3_GND	= 0b111
				};};


				Ads1115(mcu::I2C_master& i2c);

	void			setDataRate(DATA_RATE::type dataRate);
	void			setScale(SCALE::type fullScale);
	void			setInput(INPUT::type input);
	void			setContinuousConversion(bool b=true);

	int16_t			getData(void);
	float			getVoltage(void)
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
	float			getVoltage(INPUT::type input)
				{
					setInput(input);
					return getVoltage();
				}



private:
				struct REGISTER_ADDRESS{ enum type{
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

	mcu::I2C_master& 	_i2c;
	const uint8_t		ADDRESS;
	SCALE::type 		_fullScale;

};






/** ============================================================================================ **/
#endif // __ADS1115_HPP_INCLUDED__
