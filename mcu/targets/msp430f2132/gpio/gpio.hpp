// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*    AUTOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|										|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

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

#ifndef __MSP430F2132_GPIO_HPP_INCLUDED__
#define __MSP430F2132_GPIO_HPP_INCLUDED__



/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"
#ifdef __MSP430F2132_GPIO_ENABLED__

#include <stdint.h>
#include "hal/mcu/virtual/gpio/gpio.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace hal{namespace uc{namespace msp430f2132{
	class Gpio;
}}}


/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	GPIO
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/
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
					bool	config(	DIRECTION::type direction =DIRECTION::INPUT,
							RESISTOR::type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PORT 2 ----------------------------------------------------------
 	class 			Port2 : public hal::uc::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::type direction =DIRECTION::INPUT,
							RESISTOR::type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PORT 3 ----------------------------------------------------------
 	class 			Port3 : public hal::uc::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::type direction =DIRECTION::INPUT,
							RESISTOR::type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PRIVATE INSTANCES -----------------------------------------------
 	Port1			_port1;
 	Port2			_port2;
 	Port3			_port3;
};





/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	hal::uc::msp430f2132::Gpio :: GLOBAL VARIABLE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

namespace hal{namespace uc{namespace msp430f2132{
	extern hal::uc::msp430f2132::Gpio gpio;
}}}


/** ============================================================================================ **/
#endif // __MSP430F2132_GPIO_ENABLED__
#endif // __MSP430F2132_GPIO_HPP_INCLUDED__
