// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015, Individual contributors, see AUTHORS file. 	|
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




#ifndef __YAHAL_MCU_M430F5309_GPIO_HPP_INCLUDED__
#define __YAHAL_MCU_M430F5309_GPIO_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/targets/msp430f5309_config.hpp"
#ifdef __YAHAL_MCU_MSP430F5309_GPIO_ENABLED__

#include <stdint.h>
#include "../../../modules/gpio/gpio.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class Gpio;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Gpio : public yahal::mcu::Gpio
{
public:				// PORT ACCESS -----------------------------------------------------
 	yahal::mcu::Gpio::Port&	port(uint8_t portNumber);


private:			// INITIALIZATION
	void			doInit(void);


private:
 				// PORT 1 ----------------------------------------------------------
 	class 			Port1 : public yahal::mcu::Gpio::Port
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
 	class 			Port2 : public yahal::mcu::Gpio::Port
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
 	class 			Port3 : public yahal::mcu::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::Type direction =DIRECTION::INPUT,
							RESISTOR::Type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PORT 4 ----------------------------------------------------------
 	class 			Port4 : public yahal::mcu::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::Type direction =DIRECTION::INPUT,
							RESISTOR::Type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PORT 5 ----------------------------------------------------------
 	class 			Port5 : public yahal::mcu::Gpio::Port
				{
				public:
					bool	config(	DIRECTION::Type direction =DIRECTION::INPUT,
							RESISTOR::Type resistor =RESISTOR::DISABLED,
							uint8_t mask = 0xFF);

					void	set(uint8_t value, uint8_t mask=0xFF);
					uint8_t	get(uint8_t mask=0xFF)const;
					uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


 				// PORT 6 ----------------------------------------------------------
 	class 			Port6 : public yahal::mcu::Gpio::Port
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
 	Port1			_port1;
 	Port2			_port2;
 	Port3			_port3;
 	Port4			_port4;
 	Port5			_port5;
 	Port6			_port6;
};



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{
	extern yahal::mcu::targets::msp430f5309::Gpio gpio;
}



/* ---------------------------------------------------------------------------------------------- */
#endif // __YAHAL_MCU_MSP430F5309_GPIO_ENABLED__
#endif // __YAHAL_MCU_MSP430F5309_GPIO_HPP_INCLUDED__
