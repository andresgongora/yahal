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


#include "port.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_PORT1

#include <msp430f5309.h>
#include "../../../../error/assert.hpp"
//#include "../../empty/gpio/port.hpp"
#include "../../../../utility/data/mask.hpp"


/* =================================================================================================
	PORT::PIN
================================================================================================= */
/*template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin::Pin(uint8_t pin_number) :
	pin_bit_(1<<pin_number)
{}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin::setAsInput(void)
{
	Port<T_DIR,T_OUT,T_IN,T_REN>::getConstInstance().setAsInput(pin_bit_);
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin::setAsOutput()
{
	//Port<T_DIR,T_OUT,T_IN,T_REN>::getConstInstance().setAsOutput(pin_bit_);
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin::set(bool b)
{
	//if(b)	{ Port<T_DIR,T_OUT,T_IN,T_REN>::getConstInstance().set(pin_bit_,pin_bit_); }
	//else	{ Port<T_DIR,T_OUT,T_IN,T_REN>::getConstInstance().set(0x00,pin_bit_); }
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
bool yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin::get() const
{
	//return Port<T_DIR,T_OUT,T_IN,T_REN>::getConstInstance().get();
	return false;
}

template<volatile uint8_t& T_DIR, volatile uint8_t& T_OUT, volatile uint8_t& T_IN, volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin::toggle()
{
	//return Port<T_DIR,T_OUT,T_IN,T_REN>::getConstInstance().toggle();
}
*/


/* =================================================================================================
	PORT::PIN
================================================================================================= */
/*yahal::mcu::targets::msp430f5309::Gpio::Pin::Pin(uint8_t pin_number) :
	pin_bit_(1<<pin_number) ///< If pin_number greate than 7, then, pin_bit_ = 0x00
{}
*/
/*
template<>
yahal::mcu::targets::msp430f5309::Port1&
yahal::mcu::targets::msp430f5309::Gpio::PinTemplate<yahal::mcu::targets::msp430f5309::Port1> =
	yahal::mcu::targets::msp430f5309::Gpio::port1_;


template<typename T_PORT>
void yahal::mcu::targets::msp430f5309::Gpio::PinTemplate<T_PORT>::setAsInput(void)
{
	port_.setAsInput(pin_bit_);
}

template<typename T_PORT>
void yahal::mcu::targets::msp430f5309::Gpio::PinTemplate<T_PORT>::setAsOutput(void)
{
	port_.setAsOutput(pin_bit_);
}

template<typename T_PORT>
void yahal::mcu::targets::msp430f5309::Gpio::PinTemplate<T_PORT>::set(bool b)
{
	if(b)	{ port_.set(pin_bit_,pin_bit_); }
	else	{ port_.set(0x00,pin_bit_); }
}

template<typename T_PORT>
bool yahal::mcu::targets::msp430f5309::Gpio::PinTemplate<T_PORT>::get(void) const
{
	return port_.get(pin_bit_);
}

template<typename T_PORT>
void yahal::mcu::targets::msp430f5309::Gpio::PinTemplate<T_PORT>::toggle(void)
{
	port_.toggle(pin_bit_);
}

/*yahal::mcu::targets::msp430f5309::Gpio::Pin::Pin(yahal::mcu::modules::Port& port,
						 uint8_t pin_number) :
	port_(port),
	pin_bit_(1<<pin_number) ///< If pin_number greate than 7, then, pin_bit_ = 0x00
{}

void yahal::mcu::targets::msp430f5309::Gpio::Pin::setAsInput(void)
{
	port_.setAsInput(pin_bit_);
}

void yahal::mcu::targets::msp430f5309::Gpio::Pin::setAsOutput(void)
{
	port_.setAsOutput(pin_bit_);
}

void yahal::mcu::targets::msp430f5309::Gpio::Pin::set(bool b)
{
	if(b)	{ port_.set(pin_bit_,pin_bit_); }
	else	{ port_.set(0x00,pin_bit_); }
}

bool yahal::mcu::targets::msp430f5309::Gpio::Pin::get(void) const
{
	return port_.get(pin_bit_);
}

void yahal::mcu::targets::msp430f5309::Gpio::Pin::toggle(void)
{
	port_.toggle(pin_bit_);
}
*/




/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_PORT#
