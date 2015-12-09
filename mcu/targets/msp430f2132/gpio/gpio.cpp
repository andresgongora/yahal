// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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





/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <mcu/targets/msp430f2132/gpio/gpio.hpp>
#ifdef __MSP430F2132_GPIO_ENABLED__

#include <msp430f2132.h>



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Gpio
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool hal::uc::msp430f2132::Gpio::init(void)
{
	bool success = true;
	this->clearErrorCode();

	P1OUT = P2OUT = P3OUT = 0;	// Clear outputs

	success &= _port1.config(DIRECTION::INPUT, RESISTOR::DISABLED);
	success &= _port2.config(DIRECTION::INPUT, RESISTOR::DISABLED);
	success &= _port3.config(DIRECTION::INPUT, RESISTOR::DISABLED);

	if(!success)	this->setErrorCode(ERROR::COULD_NOT_INITIALIZE_PORT);
	else		this->setInitialized();
	return success;
}


hal::uc::Gpio::Port& hal::uc::msp430f2132::Gpio::port(uint8_t portNumber)
{
	switch(portNumber)
	{
	case 1: return _port1;
	case 2: return _port2;
	case 3: return _port3;
	default:
		this->setErrorCode(ERROR::TRYING_TO_ACCESS_NON_EXISTANT_PORT);
		for(;;);	//TODO: TRAP
	}

}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Gpio::Port1
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool hal::uc::msp430f2132::Gpio::Port1::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P1SEL  &= ~mask;		// I/0 function is selected
	P1SEL2 &= ~mask;
	P1DIR   = (direction == DIRECTION::OUTPUT ? P1DIR|mask : P1DIR & (~mask));// 0 = IN; 1 = OUT


	// RESISTOR
	if(direction == DIRECTION::INPUT && resistor == RESISTOR::PULLUP)
	{
		P1REN |= mask;		// Enable resistor
		P1OUT |= mask; 		// Configure as pullup
	}
	else if(direction == DIRECTION::INPUT && resistor == RESISTOR::PULLDOWN)
	{
		P1REN &= ~mask;		// Disable resistor - Not pulldown not available
		return false;
	}
	else
	{
		P1REN &= ~mask;		// Disable resistor
	}

	return true;
}


void hal::uc::msp430f2132::Gpio::Port1::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P1OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P1OUT = ( oldRegOut & andMask ) | orMask;
}


uint8_t	hal::uc::msp430f2132::Gpio::Port1::get(uint8_t mask)const
{
	return P1IN & mask;
}


uint8_t	hal::uc::msp430f2132::Gpio::Port1::getOutput(uint8_t mask)const
{
	return P1OUT & mask;
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Gpio::Port2
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool hal::uc::msp430f2132::Gpio::Port2::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P2SEL  &= ~mask;		// I/0 function is selected
	P2SEL2 &= ~mask;
	P2DIR   = (direction == DIRECTION::OUTPUT ? P2DIR|mask : P2DIR & (~mask));// 0 = IN; 1 = OUT


	// RESISTOR
	if(direction == DIRECTION::INPUT && resistor == RESISTOR::PULLUP)
	{
		P2REN |= mask;		// Enable resistor
		P2OUT |= mask; 		// Configure as pullup
	}
	else if(direction == DIRECTION::INPUT && resistor == RESISTOR::PULLDOWN)
	{
		P2REN &= ~mask;		// Disable resistor - Not pulldown not available
		return false;
	}
	else
	{
		P2REN &= ~mask;		// Disable resistor
	}

	return true;
}


void hal::uc::msp430f2132::Gpio::Port2::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P2OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P2OUT = ( oldRegOut & andMask ) | orMask;
}


uint8_t	hal::uc::msp430f2132::Gpio::Port2::get(uint8_t mask)const
{
	return P2IN & mask;
}


uint8_t	hal::uc::msp430f2132::Gpio::Port2::getOutput(uint8_t mask)const
{
	return P2OUT & mask;
}


/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Gpio::Port3
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool hal::uc::msp430f2132::Gpio::Port3::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P3SEL  &= ~mask;		// I/0 function is selected
	//P3SEL2 &= ~mask;		// Port 3 has no SEL2
	P3DIR   = (direction == DIRECTION::OUTPUT ? P3DIR|mask : P3DIR & (~mask));// 0 = IN; 1 = OUT


	// RESISTOR
	if(direction == DIRECTION::INPUT && resistor == RESISTOR::PULLUP)
	{
		P3REN |= mask;		// Enable resistor
		P3OUT |= mask; 		// Configure as pullup
	}
	else if(direction == DIRECTION::INPUT && resistor == RESISTOR::PULLDOWN)
	{
		P3REN &= ~mask;		// Disable resistor - Not pulldown not available
		return false;
	}
	else
	{
		P3REN &= ~mask;		// Disable resistor
	}

	return true;
}


void hal::uc::msp430f2132::Gpio::Port3::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P3OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P3OUT = ( oldRegOut & andMask ) | orMask;
}


uint8_t	hal::uc::msp430f2132::Gpio::Port3::get(uint8_t mask)const
{
	return P3IN & mask;
}


uint8_t	hal::uc::msp430f2132::Gpio::Port3::getOutput(uint8_t mask)const
{
	return P3OUT & mask;
}








/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Gpio :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace hal{namespace uc{namespace msp430f2132{
	hal::uc::msp430f2132::Gpio gpio;
}}}

/** ============================================================================================ **/
#endif // __MSP430F2132_GPIO_ENABLED__
