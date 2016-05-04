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
#include "../../../../error/assert.hpp"
#include "../../empty/gpio/port.hpp"



namespace{
	struct Pullup{ enum Type{
		HIGH,
		LOW,
		DISABLE
	};};
}



/***********************************************************************************************//**
 * @brief
 * Private functions have access to HW registers and are accesible for port as well as pins.
 **************************************************************************************************/
template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
class yahal::mcu::targets::msp430f5309::Port : public yahal::mcu::modules::Port
{
private:
				/***************************************************************//**
				 * @brief
				 ******************************************************************/
				class Configuration
				{
					class PullupResistor
					{
					public:
						void disable(uint8_t mask = 0xFF) {
							configure(Pullup::DISABLE,mask);
						}
						void high(uint8_t mask = 0xFF) {
							configure(Pullup::HIGH,mask);
						}
						void low(uint8_t mask = 0xFF) {
							configure(Pullup::LOW,mask);
						}
					};

				public:
					PullupResistor 	pullup;
				};
	

				/***************************************************************//**
				 * @brief
				 ******************************************************************/
				class Pin : public yahal::mcu::modules::Port::Pin
				{
					class Configuration
					{
						class PullupResistor
						{
							const uint8_t& 	mask_;

						public:
							void disable() {
								configure(Pullup::DISABLE,mask_);
							}
							void high() {
								configure(Pullup::HIGH,mask_);
							}
							void low() {
								configure(Pullup::LOW,mask_);
							}

							PullupResistor(const uint8_t& mask) :
								mask_(mask)
							{}
						};

					public:
						Configuration(const uint8_t& mask) : pullup(mask) {}
						PullupResistor 	pullup;
					};



				public:
							Pin(uint8_t pin_number) :
								pin_bit_(0x01<<pin_number),
								config(pin_bit_)
							{}

					virtual void	setAsInput(void) {setAsInput_(pin_bit_);}
					virtual void	setAsOutput(void){setAsOutput_(pin_bit_);}
					virtual void	set(bool b)	 {set_(pin_bit_, pin_bit_);}
					virtual bool	get(void) const  {return get_(pin_bit_);}
					virtual void	toggle(void)	 {toggle_(pin_bit_);}

					Configuration	config;

				private:
					const uint8_t 	pin_bit_;


				};



				//------------------------------------------------------------------
private:
				friend class yahal::mcu::targets::msp430f5309::Msp430f5309;

				Port(void) :
					pin0(0), pin1(1), pin2(2), pin3(3),
					pin4(4), pin5(5), pin6(6), pin7(7)
				{}


public:
	virtual void		setAsInput(uint8_t mask = 0xFF)		{ setAsInput_(mask); }
	virtual void 		setAsOutput(uint8_t mask = 0xFF)	{ setAsOutput_(mask); }
	virtual void 		set(uint8_t value, uint8_t mask = 0xFF) { set_(value,mask); }
	virtual uint8_t		get(uint8_t mask = 0xFF) const		{ return get_(mask); }
	virtual void 		toggle(uint8_t mask = 0xFF)		{ toggle_(mask); }


//	inline Configuration	config(uint8_t mask = 0xFF)	{ return Configuration(mask); }
	Configuration		config;
	Pin			pin0,pin1,pin2,pin3,pin4,pin5,pin6,pin7;

private:
	virtual
	modules::Port::Pin&	pin(uint8_t pin_number){
					assert(pin_number <= 7);

					switch(pin_number)
					{
					case 0: return pin0;
					case 1: return pin1;
					case 2: return pin2;
					case 3: return pin3;
					case 4: return pin4;
					case 5: return pin5;
					case 6: return pin6;
					case 7: return pin7;
					default:return pin0; //TODO!!!!!! RETURN EMPTY
					}
				}


				//------------------------------------------------------------------
private:
	static void 		setAsInput_(uint8_t mask)
				{
					T_DIR &= ~mask;
				}

	static void 		setAsOutput_(uint8_t mask)
				{
					T_DIR |= mask;
					configure(Pullup::DISABLE,mask);
				}

	static void 		set_(uint8_t value, uint8_t mask)
				{
					T_OUT = yahal::utility::data::setMasked(T_OUT, value, mask);
				}

	static uint8_t		get_(uint8_t mask)
				{
					uint8_t input = ~T_DIR & T_IN;
					uint8_t output = T_DIR & T_OUT;
					return (input|output) & mask;
				}

	static void 		toggle_(uint8_t mask)
				{
					T_OUT ^= mask;
				}

	static void		configure( Pullup::Type pullup, uint8_t mask)
				{
					// Enable pullup only on input pins
					uint8_t input_pins = ~T_DIR & mask;

					switch(pullup)
					{
					case Pullup::HIGH:
						T_REN |= input_pins;	// Enable resistor
						T_OUT |= input_pins;	// Set as pull-UP
						break;
					case Pullup::LOW:
						T_REN |= input_pins;	// Enable resistor
						T_OUT &= ~input_pins;	// Set as pull-DOWN
						break;
					default:
					case Pullup::DISABLE:
						T_REN &= ~mask;
						break;
					}
				}
};



#endif	// YAHAL_MCU_MSP430F5309_ENABLE_PORT#

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
