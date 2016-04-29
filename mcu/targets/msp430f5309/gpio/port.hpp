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


#ifndef __YAHAL_MCU_MSP430F5309_PORT_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_PORT_HPP_INCLUDED__


#include "../../../config/targets/msp430f5309.hpp"
#if	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT1 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT2 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT3 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT4 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT5 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT6 )


#include <stdint.h>
#include "../../../modules/gpio/port.hpp"
#include "../msp430f5309_namespace.hpp"
#include "../../../../cool/src/pattern/creational/singleton.hpp"
#include <msp430f5309.h>
#include "../../../../utility/data/mask.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
class yahal::mcu::targets::msp430f5309::Port : public yahal::mcu::modules::Port
{
				class Configuration
				{
					class PullupResistor
					{
					public:
						void disable(uint8_t mask =0xFF)
						{
							T_REN &= ~mask;
						}

						void high(uint8_t mask =0xFF)
						{
							uint8_t input_pins = ~T_DIR & mask; 	// Enable pullup only on input pins
							T_REN |= input_pins;			// Enable resistor
							T_OUT |= input_pins;			// Set as pull-UP
						}

						void low(uint8_t mask =0xFF)
						{
							uint8_t input_pins = ~T_DIR & mask; 	// Enable pullup only on input pins
							T_REN |= input_pins;			// Enable resistor
							T_OUT &= ~input_pins;			// Set as pull-DOWN
						}
					};
				public:
					PullupResistor	pullup;
				};

				class Pin : public yahal::mcu::modules::Port::Pin
				{
				public:
							Pin(uint8_t pin_number) :
								pin_bit_(0x01<<pin_number)
							{}

					virtual void	setAsInput(void) {
						T_DIR &= ~pin_bit_;
					}

					virtual void	setAsOutput(void) {
						T_DIR |= pin_bit_;
					}

					virtual void	set(bool b) {
						if(b)	{ T_OUT |= pin_bit_; }
						else	{ T_OUT &= ~pin_bit_; }
					}

					virtual bool	get(void) const {
						return T_IN & pin_bit_;
					}

					virtual void	toggle(void) {
						T_OUT ^= pin_bit_;
					}

					const uint8_t 	pin_bit_;
				};

				//------------------------------------------------------------------
private:
				Port(void) :
					pin0(0),
					pin1(1),
					pin2(2),
					pin3(3),
					pin4(4),
					pin5(5),
					pin6(6),
					pin7(7)
				{}

				friend class yahal::mcu::targets::msp430f5309::Msp430f5309;

public:
	virtual void		setAsInput(uint8_t mask = 0xFF) {
					T_DIR &= ~mask;
				}

	virtual void 		setAsOutput(uint8_t mask = 0xFF) {
					T_DIR |= mask;
				}

	virtual void 		set(uint8_t value, uint8_t mask = 0xFF) {
					T_OUT = yahal::utility::data::setMasked(T_OUT, value, mask);
				}

	virtual uint8_t		get(uint8_t mask = 0xFF) const {
					return T_IN & mask;
				}

	virtual void 		toggle(uint8_t mask = 0xFF) {
					T_OUT ^= mask;
				}


	Configuration		config;
	Pin			pin0,pin1,pin2,pin3,pin4,pin5,pin6,pin7;


};

#endif // YAHAL_MCU_MSP430F5309_ENABLE_PORT#



/* =================================================================================================
	PORT TYPEDEFS
================================================================================================= */


namespace yahal{
namespace mcu{
namespace targets{
namespace msp430f5309{

#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT1
	typedef Port<P1DIR,P1OUT,P1IN,P1REN> Port1;
#endif

#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT2
	typedef Port<P2DIR,P2OUT,P2IN,P2REN> Port2;
#endif

#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT2
	typedef Port<P3DIR,P3OUT,P3IN,P3REN> Port3;
#endif

#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT2
	typedef Port<P4DIR,P4OUT,P4IN,P4REN> Port4;
#endif

#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT2
	typedef Port<P5DIR,P5OUT,P5IN,P5REN> Port5;
#endif

#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT2
	typedef Port<P6DIR,P6OUT,P6IN,P6REN> Port6;
#endif

}	// namespace msp430f5309
}	// namespace targets
}	// namespace mcu
}	// namespace yahal

/* ---------------------------------------------------------------------------------------------- */

#endif // __YAHAL_MCU_MSP430F5309_PORT_HPP_INCLUDED__
