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



#ifndef __MSP430F2132_GPIO_HPP_INCLUDED__
#define __MSP430F2132_GPIO_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"
#ifdef __MSP430F2132_GPIO_ENABLED__

#include <stdint.h>
#include "hal/mcu/virtual/gpio/gpio.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace hal{namespace uc{namespace msp430f2132{
	class Gpio;
}}}


/* ============================================================================================== */
 *	GPIO
 * ============================================================================================== */
class hal::uc::msp430f2132::Gpio : public hal::uc::Gpio
{
public:
	bool			init(void);
 	hal::uc::Gpio::Port&	port(uint8_t portNumber);


private:
 				// PORT 1 ----------------------------------------------------------
 	class 			Port1 : public hal::uc::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::Type direction =DIRECTION::INPUT,
							RESISTOR::Type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PORT 2 ----------------------------------------------------------
 	class 			Port2 : public hal::uc::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::Type direction =DIRECTION::INPUT,
							RESISTOR::Type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PORT 3 ----------------------------------------------------------
 	class 			Port3 : public hal::uc::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::Type direction =DIRECTION::INPUT,
							RESISTOR::Type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PRIVATE INSTANCES -----------------------------------------------
 	Port1			port1_;
 	Port2			port2_;
 	Port3			port3_;
};





/* ============================================================================================== */
 *	hal::uc::msp430f2132::Gpio :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	extern hal::uc::msp430f2132::Gpio gpio;
}}}


/* ---------------------------------------------------------------------------------------------- */
#endif // __MSP430F2132_GPIO_ENABLED__
#endif // __MSP430F2132_GPIO_HPP_INCLUDED__
