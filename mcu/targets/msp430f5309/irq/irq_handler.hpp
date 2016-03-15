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

#ifndef __YAHAL_MCU_MSP430F5309_IRQ_HANDLER_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_IRQ_HANDLER_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/targets/msp430f5309.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_IRQ


#include "../../../modules/irq/irq_handler.hpp"
#include "../msp430f5309_namespace.hpp"
#include "../../../../utility/oop/singleton.hpp"
#include "../../../../utility/oop/service_locator.hpp"
#include <stdint.h>



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::IrqHandler : public yahal::mcu::modules::IrqHandler
{
public:
				class IsrHandler
				{
				public:
					virtual void isr(uint8_t) = 0;
				};

				class NullIsrHandler : public IsrHandler
				{
				public:
					virtual void isr(uint8_t) {}
				} static NULL_ISR_HANDLER;

				// -----------------------------------------------------------------
public:
	virtual void		enableGlobalInterrupts(void);
	virtual void		disableGlobalInterrupts(void);

				// -----------------------------------------------------------------


#ifdef YAHAL_MCU_MSP430F5309_ENABLE_ADC_10
		static void		ADC_10_ISR(void);
#endif


#ifdef YAHAL_MCU_MSP430F5309_USCI_B1_ENABLED
		static void		USCI_B1_ISR(void);
#endif





#ifdef YAHAL_MCU_MSP430F5309_ENABLE_TIMER_A1
public:
				class TimerA1 : IsrHandler
				{
				public:
					struct Irq{ enum Type{
						TIMER,
						CCR0,
						CCR1,
						CCR2
					};} static const IRQ;

					TimerA1(void) { IrqHandler::timer_a1_.set(*this); }
					//virtual void isr(uint8_t) {} //NO-OP required by service locator
//					enableIrq(void)		{TA1CTL |= TAIE;}
				};

private:
	static void		TIMER1_A1_ISR(void);	///< TIMER_A1 IRQ for Overflow, CCR1 & CCR2
	static void		TIMER1_A0_ISR(void);	///< TIMER_A1 IRQ for CCR0

	static yahal::utility::oop::ServiceLocator<IsrHandler> timer_a1_;
#endif







};



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_MSP430F5309_ENABLE_IRQ
#endif 	// __YAHAL_MCU_MSP430F5309_IRQ_HANDLER_HPP_INCLUDED__
