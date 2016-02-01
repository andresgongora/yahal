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

#include <mcu/targets/msp430f5309/adc_10/adc_10.hpp>
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309
#if YAHAL_MCU_MSP430F5309_ADC_10_ENABLED == true

#include <msp430f5309.h>
#include "../../../config/targets/msp430f5309/adc_10.hpp"



/* =================================================================================================
	TIMER A1
================================================================================================= */

yahal::mcu::targets::msp430f5309::Adc10	\
yahal::mcu::targets::msp430f5309::Adc10::instance_(yahal::mcu::targets::msp430f5309::config::adc_10);


yahal::mcu::targets::msp430f5309::Adc10&
yahal::mcu::targets::msp430f5309::Adc10::getInstance(void)
{
	return instance_;
}

/* ---------------------------------------------------------------------------------------------- */


yahal::mcu::targets::msp430f5309::Adc10::Adc10(const Configuration& configuration) :
	configuration_(configuration)
{}




bool yahal::mcu::targets::msp430f5309::Adc10::init(void)
{
	ADC10CTL0 = 0x00;	///< Disable ADC10ENC while changing configuraiton

	ADC10CTL0 = ADC10SHT_4 + ADC10ON;
	ADC10CTL1 = ADC10SHP + ADC10SSEL_3 + ADC10DIV_7;
	ADC10CTL2 = ADC10RES;
	ADC10MCTL0 = ADC10SREF_7;
	P6SEL = 0xFF;

	ADC10CTL0 |= ADC10ENC;	///< Enable ADC10ENC
	return true;
}

/* ---------------------------------------------------------------------------------------------- */

uint16_t yahal::mcu::targets::msp430f5309::Adc10::convert(void)
{
	ADC10CTL0 |= ADC10SC;	// Start conversion

	while(ADC10CTL1 & ADC10BUSY);
	volatile unsigned long long int i;
	for(i=1000; i>0; i--);
	return ADC10MEM0;
}


void yahal::mcu::targets::msp430f5309::Adc10::setChannel(std::size_t channel)
{
	ADC10CTL0 &= ~ADC10ENC;	// Disable ADC10ENC
	ADC10MCTL0 = ADC10SREF_7 + (0x0F & channel);
	ADC10CTL0 |= ADC10ENC + ADC10SC;	// Enable ADC10ENC + Start conversion
	while(ADC10CTL1 & ADC10BUSY);
}



/* ---------------------------------------------------------------------------------------------- */

void yahal::mcu::targets::msp430f5309::Adc10::isr(Irq::Type irq)
{
	switch (irq) {

	default:
		break;
	}
}



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ADC_10_ENABLED == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
