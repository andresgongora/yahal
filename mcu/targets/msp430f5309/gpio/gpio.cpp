// 1 TAB = 8 SPACES //

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "gpio.hpp"
#ifdef __MCU_MSP430F5309_GPIO_ENABLED__

#include <msp430f5309.h>



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

void mcu::targets::msp430f5309::Gpio::doInit(void)
{
	bool success = true;

	P1OUT = P2OUT = P3OUT = P4OUT = P5OUT = P6OUT = 0;	// Clear outputs

	success &= _port1.config(DIRECTION::INPUT, RESISTOR::DISABLED);
	success &= _port2.config(DIRECTION::INPUT, RESISTOR::DISABLED);
	success &= _port3.config(DIRECTION::INPUT, RESISTOR::DISABLED);
	success &= _port4.config(DIRECTION::INPUT, RESISTOR::DISABLED);
	success &= _port5.config(DIRECTION::INPUT, RESISTOR::DISABLED);
	success &= _port6.config(DIRECTION::INPUT, RESISTOR::DISABLED);

	if(!success)	this->setErrorCode(ERROR::COULD_NOT_INITIALIZE_PORT);
}


mcu::Gpio::Port& mcu::targets::msp430f5309::Gpio::port(uint8_t portNumber)
{
	switch(portNumber)
	{
	case 1: return _port1;
	case 2: return _port2;
	case 3: return _port3;
	case 4: return _port4;
	case 5: return _port5;
	case 6: return _port6;
	default:
		this->setErrorCode(ERROR::TRYING_TO_ACCESS_NON_EXISTANT_PORT);
		for(;;);	//TODO: TRAP
	}
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio::Port1
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool mcu::targets::msp430f5309::Gpio::Port1::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P1SEL  &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P1DIR   = (direction == DIRECTION::OUTPUT ? P1DIR|mask : P1DIR & (~mask));


	// RESISTOR
	if(resistor == RESISTOR::PULLUP && direction == DIRECTION::INPUT)
	{
		P1REN |= mask;		// Enable resistor
		P1OUT |= mask; 		// Configure as pullup
	}
	else if(resistor == RESISTOR::PULLDOWN && direction == DIRECTION::INPUT)
	{
		P1REN |= mask;		// Enable resistor
		P1OUT &= (~mask);	// Configure as pulldown
	}
	else
	{
		P1REN &= ~mask;		// Disable resistor
	}

	return true;
}

void mcu::targets::msp430f5309::Gpio::Port1::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P1OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P1OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	mcu::targets::msp430f5309::Gpio::Port1::get(uint8_t mask)const {return P1IN & mask;}
uint8_t	mcu::targets::msp430f5309::Gpio::Port1::getOutput(uint8_t mask)const {return P1OUT & mask;}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio::Port2
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool mcu::targets::msp430f5309::Gpio::Port2::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P2SEL  &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P2DIR   = (direction == DIRECTION::OUTPUT ? P2DIR|mask : P2DIR & (~mask));


	// RESISTOR
	if(resistor == RESISTOR::PULLUP && direction == DIRECTION::INPUT)
	{
		P2REN |= mask;		// Enable resistor
		P2OUT |= mask; 		// Configure as pullup
	}
	else if(resistor == RESISTOR::PULLDOWN && direction == DIRECTION::INPUT)
	{
		P2REN |= mask;		// Enable resistor
		P2OUT &= (~mask);	// Configure as pulldown
	}
	else
	{
		P2REN &= ~mask;		// Disable resistor
	}

	return true;
}

void mcu::targets::msp430f5309::Gpio::Port2::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P2OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P2OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	mcu::targets::msp430f5309::Gpio::Port2::get(uint8_t mask)const {return P2IN & mask;}
uint8_t	mcu::targets::msp430f5309::Gpio::Port2::getOutput(uint8_t mask)const {return P2OUT & mask;}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio::Port3
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool mcu::targets::msp430f5309::Gpio::Port3::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P3SEL  &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P3DIR   = (direction == DIRECTION::OUTPUT ? P3DIR|mask : P3DIR & (~mask));


	// RESISTOR
	if(resistor == RESISTOR::PULLUP && direction == DIRECTION::INPUT)
	{
		P3REN |= mask;		// Enable resistor
		P3OUT |= mask; 		// Configure as pullup
	}
	else if(resistor == RESISTOR::PULLDOWN && direction == DIRECTION::INPUT)
	{
		P3REN |= mask;		// Enable resistor
		P3OUT &= (~mask);	// Configure as pulldown
	}
	else
	{
		P3REN &= ~mask;		// Disable resistor
	}

	return true;
}

void mcu::targets::msp430f5309::Gpio::Port3::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P3OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P3OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	mcu::targets::msp430f5309::Gpio::Port3::get(uint8_t mask)const {return P3IN & mask;}
uint8_t	mcu::targets::msp430f5309::Gpio::Port3::getOutput(uint8_t mask)const {return P3OUT & mask;}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio::Port4
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool mcu::targets::msp430f5309::Gpio::Port4::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P4SEL  &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P4DIR   = (direction == DIRECTION::OUTPUT ? P4DIR|mask : P4DIR & (~mask));


	// RESISTOR
	if(resistor == RESISTOR::PULLUP && direction == DIRECTION::INPUT)
	{
		P4REN |= mask;		// Enable resistor
		P4OUT |= mask; 		// Configure as pullup
	}
	else if(resistor == RESISTOR::PULLDOWN && direction == DIRECTION::INPUT)
	{
		P4REN |= mask;		// Enable resistor
		P4OUT &= (~mask);	// Configure as pulldown
	}
	else
	{
		P4REN &= ~mask;		// Disable resistor
	}

	return true;
}

void mcu::targets::msp430f5309::Gpio::Port4::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P4OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P4OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	mcu::targets::msp430f5309::Gpio::Port4::get(uint8_t mask)const {return P4IN & mask;}
uint8_t	mcu::targets::msp430f5309::Gpio::Port4::getOutput(uint8_t mask)const {return P4OUT & mask;}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio::Port5
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool mcu::targets::msp430f5309::Gpio::Port5::config(	DIRECTION::type direction,
					 	RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P5SEL  &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P5DIR   = (direction == DIRECTION::OUTPUT ? P5DIR|mask : P5DIR & (~mask));


	// RESISTOR
	if(resistor == RESISTOR::PULLUP && direction == DIRECTION::INPUT)
	{
		P5REN |= mask;		// Enable resistor
		P5OUT |= mask; 		// Configure as pullup
	}
	else if(resistor == RESISTOR::PULLDOWN && direction == DIRECTION::INPUT)
	{
		P5REN |= mask;		// Enable resistor
		P5OUT &= (~mask);	// Configure as pulldown
	}
	else
	{
		P5REN &= ~mask;		// Disable resistor
	}

	return true;
}

void mcu::targets::msp430f5309::Gpio::Port5::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P5OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P5OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	mcu::targets::msp430f5309::Gpio::Port5::get(uint8_t mask)const {return P5IN & mask;}
uint8_t	mcu::targets::msp430f5309::Gpio::Port5::getOutput(uint8_t mask)const {return P5OUT & mask;}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio::Port6
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

bool mcu::targets::msp430f5309::Gpio::Port6::config(	DIRECTION::type direction,
						RESISTOR::type resistor,
						uint8_t mask)
{
	// WRITE CONFIGURATION
	P6SEL  &= ~mask;		// I/0 function is selected// 0 = IN; 1 = OUT
	P6DIR   = (direction == DIRECTION::OUTPUT ? P6DIR|mask : P6DIR & (~mask));


	// RESISTOR
	if(resistor == RESISTOR::PULLUP && direction == DIRECTION::INPUT)
	{
		P6REN |= mask;		// Enable resistor
		P6OUT |= mask; 		// Configure as pullup
	}
	else if(resistor == RESISTOR::PULLDOWN && direction == DIRECTION::INPUT)
	{
		P6REN |= mask;		// Enable resistor
		P6OUT &= (~mask);	// Configure as pulldown
	}
	else
	{
		P6REN &= ~mask;		// Disable resistor
	}

	return true;
}

void mcu::targets::msp430f5309::Gpio::Port6::set(uint8_t value, uint8_t mask)
{
	// AUXILIAR VARIABLES
	uint8_t oldRegOut = P6OUT;
	uint8_t andMask = (~mask) | value;
	uint8_t orMask =  mask & value;


	// SET
	P6OUT = ( oldRegOut & andMask ) | orMask;
}

uint8_t	mcu::targets::msp430f5309::Gpio::Port6::get(uint8_t mask)const {return P6IN & mask;}
uint8_t	mcu::targets::msp430f5309::Gpio::Port6::getOutput(uint8_t mask)const {return P6OUT & mask;}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	mcu::targets::msp430f5309::Gpio :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace mcu{
	mcu::targets::msp430f5309::Gpio gpio;
}

/** ============================================================================================ **/
#endif // __MCU_MSP430F5309_GPIO_ENABLED__
