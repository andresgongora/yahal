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

#ifndef __YAHAL_MCU_MSP430F5309_ADC_10_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_ADC_10_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/targets/msp430f5309.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_ADC_10


#include <stdint.h>
#include <cstddef>
#include "../msp430f5309_namespace.hpp"
#include "../irq/adc_10.hpp"
#include "../../../../utility/oop/service_locator.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Adc10 :
	public yahal::mcu::targets::msp430f5309::irq::Adc10
{
public:
				struct Channel{ enum Type{
					A0	= 0,
					A1	= 1,
					A2	= 2,
					A3	= 3,
					A4	= 4,
					A5	= 5,
					A6	= 6,
					A7	= 7,
					A8	= 8,
					A9	= 9,
					TEMP	= 10,	///< Temperature sense
					BATT	= 11,	///< Battery sense
					A12	= 12,
					A13	= 13,
					A14	= 14,
					A15	= 15
				};} static const CHANNEL;


				struct Mode{ enum Type{
					SINGLE_CHANNEL		= 0,
					SINGLE_AUTOSCAN		= 1,
					CONTINUOUS_CHANNEL	= 2,
					CONTINUOUS_AUTOSCAN	= 3
				};} static const MODE;


				struct ClockSource{ enum Type{
					MODCLK	= 0,
					ACLK	= 1,
					MCLK	= 2,
					SMCLK	= 3
				};} static const CLOCK_SOURCE;


				struct ClockDivider{ enum Type{
					// 4 MSBit = DIVIDER | 4 LSBit PREDIVIDER
					DIVIDER_1	= 0x00,
					DIVIDER_2	= 0x01,
					DIVIDER_3	= 0x02,
					DIVIDER_4	= 0x03,
					DIVIDER_5	= 0x04,
					DIVIDER_6	= 0x05,
					DIVIDER_7	= 0x06,
					DIVIDER_8	= 0x07,

					// 4 MSBit = DIVIDER | 4 LSBit PREDIVIDER
					DIVIDER_12	= 0x12,
					DIVIDER_16	= 0x13,
					DIVIDER_20	= 0x14,
					DIVIDER_24	= 0x15,
					DIVIDER_28	= 0x16,
					DIVIDER_32	= 0x17,

					// 4 MSBit = DIVIDER | 4 LSBit PREDIVIDER
					DIVIDER_64	= 0x20,
					DIVIDER_128	= 0x21,
					DIVIDER_256	= 0x22,
					DIVIDER_512	= 0x23,
					DIVIDER_1024	= 0x24,
					DIVIDER_2048	= 0x25,
					DIVIDER_4096	= 0x26,
					DIVIDER_8192	= 0x27
				};} static const CLOCK_DIVIDER;


				struct Format{ enum Type{
					UNSIGNED	= 0,
					SIGNED		= 1
				};} static const FORMAT;


				struct VoltageReference{ enum Type{
					AVCC_AVSS		= 0,
					VREF_AVSS		= 1,
					VEREFPBUFF_AVSS		= 2,	///< VEREF+ buffered
					VEREFP_AVSS		= 3,	///< VEREF+ not buffered
					AVCC_VEREFN		= 4,
					VREF_VEREFN		= 5,
					VEREFPBUFF_VEREFN	= 6,	///< VEREF+ buffered
					VEREFP_VEREFN		= 7,	///< VEREF+ not buffered
				};} static const VOLTAGE_REFERENCE;


				struct Resolution{ enum Type{
					BIT_8	= 0,
					BIT_10	= 1
				};} static const RESOLUTION;

				// -----------------------------------------------------------------
public:
				class AutoscanHandler
				{
				protected:
					friend class Adc10;
					virtual void handleAdc(uint8_t channel, uint16_t data) {}
				};

				AutoscanHandler mynull_; //todo

//	yahal::utility::oop::ServiceLocator<AutoscanHandler> autoscan_handler_; //todo

				// -----------------------------------------------------------------
public:
				Adc10(void);

	bool			setMode(Mode::Type mode);
	bool			setReference(VoltageReference::Type reference);
	bool			setChannel(uint8_t channel);
	bool			setSampleRate(uint8_t sample_rate);

	void			startConvertion(void);
	uint16_t		convertChannel(uint8_t channel);


private:
	void			haltForConfiguration(void);	///< ADC must be halted to change configuration
	void			resumeFromConfiguration(void);	///< Power ADC module up after configuration has been written
	uint8_t			getChannel(void);
	uint8_t			getMode(void);
	uint16_t		getRawData(void);


	void			handleAutoscan(void);
	virtual void		isr(int isr);
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_ADC_10
#endif // __YAHAL_MCU_MSP430F5309_ADC_10_HPP_INCLUDED__
