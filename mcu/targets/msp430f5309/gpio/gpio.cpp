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

#include "gpio.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_GPIO

#include <msp430f5309.h>
#include "../../../../error/assert.hpp"
#include "../../empty/gpio/gpio.hpp"
#include "../../../../utility/data/mask.hpp"



/* =================================================================================================
	GPIO
================================================================================================= */
yahal::mcu::targets::msp430f5309::Gpio::Gpio(void)
{}

yahal::mcu::modules::Gpio::Port& yahal::mcu::targets::msp430f5309::Gpio::port(uint8_t portNumber)
{
	assert(portNumber >= 1 && portNumber <= 6);

	switch(portNumber)
	{
	case 1:	return port1_;
	case 2:	return port2_;
	case 3:	return port3_;
	case 4:	return port4_;
	case 5:	return port5_;
	case 6:	return port6_;
	}
}



/* =================================================================================================
	GPIO::PORT
================================================================================================= */
template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::setAsInput(uint8_t mask)
{
	T_DIR &= ~mask;
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::setAsOutput(uint8_t mask)
{
	T_DIR |= mask;
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::set(uint8_t value, uint8_t mask)
{
	T_OUT = yahal::utility::data::setMasked(T_OUT, value, mask);
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void  yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::toggle(uint8_t mask)
{
	T_OUT ^= mask;
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::get(uint8_t mask)const
{
	return T_IN & mask;
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Gpio::Pin&
yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::pin(uint8_t pin_number)
{
	static Gpio::Pin pin(*static_cast<modules::Gpio::Port*>(this), pin_number);
	return pin;
}



/* =================================================================================================
	PORT::CONFIGURATION
================================================================================================= */
template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::Configuration::PullUpResistor::disable(uint8_t mask)
{
	T_REN &= ~mask;
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::Configuration::PullUpResistor::high(uint8_t mask)
{
	uint8_t input_pins = ~T_DIR & mask; 	// Enable pullup only on input pins
	T_REN |= input_pins;			// Enable resistor
	T_OUT |= input_pins;			// Set as pull-UP
}

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
void yahal::mcu::targets::msp430f5309::Gpio::Port<T_DIR,T_OUT,T_IN,T_REN>::Configuration::PullUpResistor::low(uint8_t mask)
{
	uint8_t input_pins = ~T_DIR & mask; 	// Enable pullup only on input pins
	T_REN |= input_pins;			// Enable resistor
	T_OUT &= ~input_pins;			// Set as pull-DOWN
}


/* =================================================================================================
	GPIO::PIN
================================================================================================= */
yahal::mcu::targets::msp430f5309::Gpio::Pin::Pin(yahal::mcu::modules::Gpio::Port& port,
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



/* =================================================================================================
	GPIO
================================================================================================= */
/*
yahal::mcu::targets::msp430f5309::Gpio::Gpio(void) :
	port1_(1),
	port2_(2),
	port3_(3),
	port4_(4),
	port5_(5),
	port6_(6)
{}


yahal::mcu::targets::msp430f5309::Gpio::Port& yahal::mcu::targets::msp430f5309::Gpio::port(uint8_t portNumber)
{
	assert(portNumber >= 1 && portNumber <= 6);

	switch(portNumber)
	{
	case 1:	return port1_;
	case 2:	return port2_;
	case 3:	return port3_;
	case 4:	return port4_;
	case 5:	return port5_;
	case 6:	return port6_;
	}
}




/* =================================================================================================
	GPIO::PORT
================================================================================================= */
/*
yahal::mcu::targets::msp430f5309::Gpio::Port::Registers
yahal::mcu::targets::msp430f5309::Gpio::Port::reg[] = {
	Registers(P1DIR,P1OUT,P1IN,P1REN),
	Registers(P2DIR,P2OUT,P2IN,P2REN),
	Registers(P3DIR,P3OUT,P3IN,P3REN),
	Registers(P4DIR,P4OUT,P4IN,P4REN),
	Registers(P5DIR,P5OUT,P5IN,P5REN),
	Registers(P6DIR,P6OUT,P6IN,P6REN)
};


void yahal::mcu::targets::msp430f5309::Gpio::Port::setAsInput(uint8_t mask)
{
	reg[port_].dir &= ~mask;
}


void yahal::mcu::targets::msp430f5309::Gpio::Port::setAsOutput(uint8_t mask)
{
	reg[port_].dir |= mask;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port::set(uint8_t value, uint8_t mask)
{
	reg[port_].out = yahal::utility::data::setMasked(reg[port_].out, value, mask);
}

void yahal::mcu::targets::msp430f5309::Gpio::Port::toggle(uint8_t mask)
{
	reg[port_].out ^= mask;
}

uint8_t	yahal::mcu::targets::msp430f5309::Gpio::Port::get(uint8_t mask)const
{
	return reg[port_].in & mask;
}

yahal::mcu::targets::msp430f5309::Gpio::Port::Pin&
yahal::mcu::targets::msp430f5309::Gpio::Port::pin(uint8_t pin_number)
{
	return pin0_;
}

/* =================================================================================================
	PORT::CONFIGURATION
================================================================================================= */

/*
void yahal::mcu::targets::msp430f5309::Gpio::Port::Configuration::PullUpResistor::disable(uint8_t mask)
{
	reg[port_].ren &= ~mask;
}

void yahal::mcu::targets::msp430f5309::Gpio::Port::Configuration::PullUpResistor::high(uint8_t mask)
{
	uint8_t input_pins = ~reg[port_].dir & mask; 	// Enable pullup only on input pins
	reg[port_].ren |= input_pins;			// Enable resistor
	reg[port_].out |= input_pins;			// Set as pull-UP
}

void yahal::mcu::targets::msp430f5309::Gpio::Port::Configuration::PullUpResistor::low(uint8_t mask)
{
	uint8_t input_pins = ~reg[port_].dir & mask; 	// Enable pullup only on input pins
	reg[port_].ren |= input_pins;			// Enable resistor
	reg[port_].out &= ~input_pins;			// Set as pull-DOWN
}
*/

/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_GPIO
