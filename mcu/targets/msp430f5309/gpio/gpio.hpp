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
#include "../../../config/mcu_config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309

#include "../../../config/targets/msp430f5309/config.hpp"
#if YAHAL_MCU_MSP430F5309_GPIO_ENABLED == true

#include <stdint.h>
#include "../../../modules/gpio/gpio.hpp"



/* ---------------------------------------------------------------------------------------------- */
namespace yahal{ namespace mcu{ namespace targets{ namespace msp430f5309{
	class Gpio;
}}}}



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Gpio : public yahal::mcu::modules::Gpio
{
public:
				struct Configuration
				{};

				static const Gpio::Direction Direction;
				static const Gpio::Resistor Resistor;

				// -----------------------------------------------------------------

				class Port1 : public yahal::mcu::modules::Gpio::Port
				{
				public:
					static Port1&	getInstance(void);
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;

				private:
							Port1(void){}	///< Singleton
					static Port1	instance_;
				};


				class Port2 : public yahal::mcu::modules::Gpio::Port
				{
				public:
					static Port2&	getInstance(void);
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;

				private:
							Port2(void){}	///< Singleton
					static Port2	instance_;
				};


				class Port3 : public yahal::mcu::modules::Gpio::Port
				{
				public:
					static Port3&	getInstance(void);
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;

				private:
							Port3(void){}	///< Singleton
					static Port3	instance_;
				};


				class Port4 : public yahal::mcu::modules::Gpio::Port
				{
				public:
					static Port4&	getInstance(void);
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;

				private:
							Port4(void){}	///< Singleton
					static Port4	instance_;
				};


				class Port5 : public yahal::mcu::modules::Gpio::Port
				{
				public:
					static Port5&	getInstance(void);
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;

				private:
							Port5(void){}	///< Singleton
					static Port5	instance_;
				};


				class Port6 : public yahal::mcu::modules::Gpio::Port
				{
				public:
					static Port6&	getInstance(void);
					virtual bool	config(	Direction::Type direction = Direction::INPUT,
								Resistor::Type resistor = Resistor::DISABLED,
								uint8_t mask = 0xFF);

					virtual void	set(uint8_t value, uint8_t mask=0xFF);
					virtual uint8_t	get(uint8_t mask=0xFF)const;
					virtual uint8_t	getOutput(uint8_t mask=0xFF)const;

				private:
							Port6(void){}	///< Singleton
					static Port6	instance_;
				};

				// -----------------------------------------------------------------
public:
	static Gpio&		getInstance(void);		///< Get singleton instance
	bool			init(void);
	virtual Port& 		port(uint8_t portNumber);	///< Get port


private:
				Gpio(const Configuration& configuration);	///< Singleton
 	static Gpio		instance_;
 	const Configuration&	configuration_;
};



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_GPIO_ENABLED == true
#endif // YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif // __YAHAL_MCU_MSP430F5309_GPIO_HPP_INCLUDED__
