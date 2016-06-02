// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------+-----------------------------------+
	|                                                                       |
	|             Yet Another Hardware Abstraction Layer (YAHAL)            |
	|                https://github.com/andresgongora/yahal                 |
	|                                                                       |
	|                                                                       |
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file. |
	| Machine Perception and Intelligent Robotics (MAPIR),                  |
	| University of Malaga. <http://mapir.isa.uma.es>                       |
	|                                                                       |
	| This program is free software: you can redistribute it and/or modify  |
	| it under the terms of the GNU General Public License as published by  |
	| the Free Software Foundation, either version 3 of the License, or     |
	| (at your option) any later version.                                   |
	|                                                                       |
	| This program is distributed in the hope that it will be useful,       |
	| but WITHOUT ANY WARRANTY; without even the implied warranty of        |
	| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
	| GNU General Public License for more details.                          |
	|                                                                       |
	| You should have received a copy of the GNU General Public License     |
	| along with this program. If not, see <http://www.gnu.org/licenses/>.  |
	|                                                                       |
	+-----------------------------------------------------------------------+ */


#ifndef __YAHAL_MCU_MSP430F5309_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_HPP_INCLUDED__


#include "../../config/config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309


#include <stdint.h>
#include <msp430f5309.h>
#include "msp430f5309_namespace.hpp"
#include "../../config/targets/msp430f5309.hpp"


#include "clk/clk.hpp"
#include "gpio/port.hpp"
#include "wdt/wdt.hpp"




/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Msp430f5309
{
protected:
				// CONSTRUCTOR
				Msp430f5309(void);


				//------------------------------------------------------------------
public:

#ifdef	YAHAL_MCU_MSP430F5309_ENABLE_CLK
	static Clk YAHAL_MCU_MSP430F5309_NAME_CLK;

#endif

#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_PORT1
	static Port1 YAHAL_MCU_MSP430F5309_NAME_PORT1;
#endif

#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_PORT2
	msp430f5309::Port2	YAHAL_MCU_MSP430F5309_NAME_PORT2;
#endif

#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_PORT3
	msp430f5309::Port3	YAHAL_MCU_MSP430F5309_NAME_PORT3;
#endif

#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_PORT4
	msp430f5309::Port4	YAHAL_MCU_MSP430F5309_NAME_PORT4;
#endif

#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_PORT5
	msp430f5309::Port5	YAHAL_MCU_MSP430F5309_NAME_PORT5;
#endif

#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_PORT6
	msp430f5309::Port6	YAHAL_MCU_MSP430F5309_NAME_PORT6;
#endif

#ifdef 	YAHAL_MCU_MSP430F5309_ENABLE_WDT
	static Wdt		YAHAL_MCU_MSP430F5309_NAME_WDT;
#endif

				//------------------------------------------------------------------





	// ADC_10
	#ifdef YAHAL_MCU_MSP430F5309_ENABLE_ADC_10
		yahal::mcu::targets::msp430f5309::Adc10 adc_10;
	#endif


	// TIMER_A1
	#ifdef YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
		yahal::mcu::targets::msp430f5309::TimerA1 timerA1;
	#endif

/*
	// USCI_B1
	#if YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED == true
		#if YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SLAVE
			yahal::mcu::targets::msp430f5309::UsciB1::I2CSlave YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MASTER
			yahal::mcu::targets::msp430f5309::UsciB1::I2CMaster YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_MULTIMASTER
			yahal::mcu::targets::msp430f5309::UsciB1::I2CMultimaster& YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#elif YAHAL_MCU_MSP430F5309_USCI_B1_MODE == YAHAL_MCU_MSP430F5309_USCI_B1_I2C_SPI
			yahal::mcu::targets::msp430f5309::UsciB1::Spi YAHAL_MCU_MSP430F5309_USCI_B1_NAME;
		#else
			#error "USCI_B1_MODE is not valid"
		#endif
	#endif





	// IRQ
	#if YAHAL_MCU_MSP430F5309_IRQ_ENABLED == true
		yahal::mcu::targets::msp430f5309::IrqHandler& irq;
	#endif*/

private:
	const uint8_t	dummy_;
};




namespace yahal{
namespace mcu{
typedef yahal::mcu::targets::msp430f5309::Msp430f5309 Target;
}
}



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif	// __YAHAL_MCU_MSP430F5309_HPP_INCLUDED__
