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


#include "irq_handler.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include <msp430f5309.h>



/* ---------------------------------------------------------------------------------------------- */
/*
void yahal::mcu::targets::msp430f5309::IrqHandler::enableGlobalInterrupts(void)
{
	_EINT();
}


void yahal::mcu::targets::msp430f5309::IrqHandler::disableGlobalInterrupts(void)
{
	_DINT();
}



/* =================================================================================================
	ADC_10
================================================================================================= */
#if YAHAL_MCU_MSP430F5309_ENABLE_ADC_10 == true
	#pragma vector = ADC10_VECTOR
	__interrupt void yahal::mcu::targets::msp430f5309::IrqHandler::ADC_10_ISR(void)
	{
		yahal::mcu::targets::msp430f5309::Adc10& adc_10 = yahal::mcu::targets::msp430f5309::Adc10::getInstance();

		switch(__even_in_range(ADC10IV,12)) {
		case  0: ///< Vector 00: No interrupts
			break;
		case  2: ///< Vector 02: Overflow
			adc_10.isr(adc_10.IRQ.OVERFLOW);
			break;
		case  4: ///< Vector 04: Over sample
			adc_10.isr(adc_10.IRQ.OVERSAMPLE);
			break;
		case  6: ///< Vector 06: Signal over threshold high level
			adc_10.isr(adc_10.IRQ.THRESHOLD_OVER);
			break;
		case  8: ///< Vector 08: Signal below threshold low level
			adc_10.isr(adc_10.IRQ.THRESHOLD_BELOW);
			break;
		case 10: ///< Vector 10: Signal inside threshold levels
			adc_10.isr(adc_10.IRQ.THRESHOLD_INSIDE);
			break;
		case 12: ///< Vector 12: ADC convertion end
			adc_10.isr(adc_10.IRQ.CONVERTION);
			break;
		default:
			break;
		}
	}
#endif





/* =================================================================================================
	TIMER_A1
================================================================================================= */
/*#if YAHAL_MCU_MSP430F5309_TIMER_A1_ENABLED == true

	yahal::mcu::targets::msp430f5309::TimerA1&	\
		yahal::mcu::targets::msp430f5309::IrqHandler::handler_timer_a1_ =	\
			yahal::mcu::targets::msp430f5309::TimerA1::getInstance();

	#pragma vector = TIMER1_A1_VECTOR
	__interrupt void yahal::mcu::targets::msp430f5309::IrqHandler::TIMER1_A1_ISR(void)
	{
		switch (__even_in_range(TA1IV,14)) {
		case  0: ///< Vector 00: No interrupts
			break;
		case  2: ///< Vector 02: CCR1
			handler_timer_a1_.isr(msp430f5309::TimerA1::Irq::CCR1);
			break;
		case  4: ///< Vector 04: CCR2
			handler_timer_a1_.isr(msp430f5309::TimerA1::Irq::CCR2);
			break;
		case  6: ///< Vector 06: reserved
			break;
		case  8: ///< Vector 08: reserved
			break;
		case 10: ///< Vector 10: reserved
			break;
		case 12: ///< Vector 12: reserved
			break;
		case 14: ///< Vector 14: TA1
			handler_timer_a1_.isr(msp430f5309::TimerA1::Irq::TIMER);
			break;
		default:
			break;
		}
	}


	#pragma vector = TIMER1_A0_VECTOR
	__interrupt void yahal::mcu::targets::msp430f5309::IrqHandler::TIMER1_A0_ISR(void)
	{
		handler_timer_a1_.isrCcr0();
	}
#endif



/* =================================================================================================
	USCI_B1
================================================================================================= */
/*#if YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true
	#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE




	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER



	#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER

		yahal::mcu::targets::msp430f5309::UsciB1&	\
		yahal::mcu::targets::msp430f5309::IrqHandler::handler_usci_b1_ =	\
			yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster::getInstance();


		#pragma vector = USCI_B1_VECTOR
		__interrupt void yahal::mcu::targets::msp430f5309::IrqHandler::USCI_B1_ISR(void)
		{
			switch (__even_in_range(UCB1IV, 12))
			{
			case  0: ///< Vector 00: No interrupts
				break;
			case  2: ///< Vector 02: Arbitration Lost
				handler_usci_b1_.isr(UsciB1::Irq::I2C_ARBITRATION_LOST);
				break;
			case  4: ///< Vector 04: Nack
				handler_usci_b1_.isr(UsciB1::Irq::I2C_NACK);
				break;
			case  6: ///< Vector 06: Start
				handler_usci_b1_.isr(UsciB1::Irq::I2C_START);
				break;
			case  8: ///< Vector 08: Stop
				handler_usci_b1_.isr(UsciB1::Irq::I2C_STOP);
				break;
			case 10: ///< Vector 10: RX Full
				handler_usci_b1_.isr(UsciB1::Irq::I2C_RX_BUFFER_FULL);
				break;
			case 12: ///< Vector 12: TX Empty
				handler_usci_b1_.isr(UsciB1::Irq::I2C_TX_BUFFER_EMPTY);
				break;
			default:
				break;
			}
		}

	#else
		#error "USCI_B1_MODE is not valid"
	#endif
#endif



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
