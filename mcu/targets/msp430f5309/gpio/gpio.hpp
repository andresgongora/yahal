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


#ifndef __YAHAL_MCU_MSP430F5309_GPIO_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_GPIO_HPP_INCLUDED__



/* ---------------------------------------------------------------------------------------------- */
#include "../../../config/targets/msp430f5309.hpp"
#ifdef YAHAL_MCU_MSP430F5309_ENABLE_GPIO


#include <stdint.h>
#include "../../../modules/gpio/gpio.hpp"
#include "../../../../utility/oop/singleton.hpp"
#include "../msp430f5309_namespace.hpp"



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Gpio : public yahal::mcu::modules::Gpio
{
private:
				class Port1 : 	public yahal::mcu::modules::Gpio::Port
				{
				public:
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual void	toggle(uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


				class Port2 : 	public yahal::mcu::modules::Gpio::Port
				{
				public:
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual void	toggle(uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


				class Port3 : 	public yahal::mcu::modules::Gpio::Port
				{
				public:
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual void	toggle(uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;

				};


				class Port4 : 	public yahal::mcu::modules::Gpio::Port
				{
				public:
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual void	toggle(uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


				class Port5 : 	public yahal::mcu::modules::Gpio::Port
				{
				public:
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual void	toggle(uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;
				};


				class Port6 :	public yahal::mcu::modules::Gpio::Port
				{
				public:
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual void	toggle(uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;
				};

				// -----------------------------------------------------------------
public:
				Gpio(void);
	virtual Port& 		port(uint8_t portNumber);

private:
	Port1			port1_;
	Port1			port2_;
	Port1			port3_;
	Port1			port4_;
	Port1			port5_;
	Port1			port6_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_GPIO
#endif // __YAHAL_MCU_MSP430F5309_GPIO_HPP_INCLUDED__
