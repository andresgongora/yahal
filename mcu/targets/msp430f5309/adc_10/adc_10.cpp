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


#include "adc_10.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_ADC_10

#include <msp430f5309.h>



/* ---------------------------------------------------------------------------------------------- */

yahal::mcu::targets::msp430f5309::Adc10::Adc10(void)
{
	ADC10CTL0 = 0x00;	///< Disable ADC10ENC while changing configuraiton

	P6SEL = 0xFF;
	ADC10CTL0 = ADC10SHT_4 + ADC10ON;
	ADC10CTL1 = ADC10SHP + ADC10SSEL_3 + ADC10DIV_7;
	ADC10CTL2 = ADC10RES;					///< 10 bit resolution
	setReference(VoltageReference::VEREFP_VEREFN);		///<WARNING_ Enables ENC

	ADC10CTL0 |= ADC10ENC;	///< Enable ADC10ENC
}

/* ---------------------------------------------------------------------------------------------- */

bool yahal::mcu::targets::msp430f5309::Adc10::setMode(Mode::Type mode)
{
	if (mode <= 3)
	{
		haltForConfiguration();

		ADC10CTL1 = (ADC10CTL1 & 0xFFF9) | (mode << 1);

		if (mode == Mode::SINGLE_AUTOSCAN || mode == Mode::SINGLE_CHANNEL) {
			irq::Adc10::disableIrq();
		} else {
			irq::Adc10::enableIrq();
		}

		resumeFromConfiguration();
		return true;
	}

	return false;
}


bool yahal::mcu::targets::msp430f5309::Adc10::setReference(VoltageReference::Type reference)
{
	if (reference <= 7)
	{
		haltForConfiguration();
		ADC10MCTL0 = (ADC10MCTL0 & 0x8F) | (reference << 4);
		resumeFromConfiguration();
		return true;
	}

	return false;
}


bool yahal::mcu::targets::msp430f5309::Adc10::setChannel(uint8_t channel)
{
	if (channel <= 15)
	{
		haltForConfiguration();
		ADC10MCTL0 = (ADC10MCTL0 & 0xF0) | channel;
		resumeFromConfiguration();
		return true;
	}

	return false;
}


bool yahal::mcu::targets::msp430f5309::Adc10::setSampleRate(uint8_t sample_rate)
{
	return false;
}

/* ---------------------------------------------------------------------------------------------- */












/*float yahal::mcu::targets::msp430f5309::Adc10::convert(uint8_t channel)
{
	setChannel(channel);

	ADC10CTL0 |= ADC10SC;	// Start conversion

	while(ADC10CTL1 & ADC10BUSY);	//TODO: Replace with RTOS IRQ semaphore

	float raw = ADC10MEM0;
	float voltage = (gain_ * raw) + configuration_.v_ref_n;
	return voltage;
}
*/

void yahal::mcu::targets::msp430f5309::Adc10::startConvertion(void)
{
	ADC10CTL0 |= ADC10SC;
}


uint16_t yahal::mcu::targets::msp430f5309::Adc10::convertChannel(uint8_t channel)
{
//	if (channel > 15)	{ return 0x0000; }
//	else 			{ return buffer_raw_[channel]; }
}











void yahal::mcu::targets::msp430f5309::Adc10::haltForConfiguration(void)
{
	ADC10CTL0 &= ~ADC10ENC;	///< Disable ADC10ENC
}


void yahal::mcu::targets::msp430f5309::Adc10::resumeFromConfiguration(void)
{
	ADC10CTL0 |= ADC10ENC;
}


uint8_t yahal::mcu::targets::msp430f5309::Adc10::getChannel(void)
{
	return ADC10MCTL0 & 0x0F;
}


uint8_t yahal::mcu::targets::msp430f5309::Adc10::getMode(void)
{
	return (ADC10CTL1 & 0x0006) >> 1;
}


uint16_t yahal::mcu::targets::msp430f5309::Adc10::getRawData(void)
{
	return ADC10MEM0;
}

/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::Adc10::handleAutoscan(void)
{
	uint8_t channel = getChannel();
	uint16_t raw_data = getRawData();
	autoscan_handler_.get().handleAdc(channel, raw_data);
}


void yahal::mcu::targets::msp430f5309::Adc10::isr(uint8_t irq)
{
	switch (irq) {

	case Irq::OVERSAMPLE:
		break;

	case Irq::OVERFLOW:
		break;

	case Irq::THRESHOLD_OVER:
		break;

	case Irq::THRESHOLD_INSIDE:
		break;

	case Irq::THRESHOLD_BELOW:
		break;

	case Irq::CONVERTION:
		handleAutoscan();
		break;

	default:
		break;
	}
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_ADC_10
