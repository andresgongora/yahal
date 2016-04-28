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
#include "../msp430f5309_namespace.hpp"
#include "../../../../cool/src/pattern/creational/singleton.hpp"
#include <msp430f5309.h>



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class yahal::mcu::targets::msp430f5309::Gpio :
	public yahal::mcu::modules::Gpio,
	public cool::pattern::creational::Singleton<Gpio>
{
private:
				class Pin : public yahal::mcu::modules::Gpio::Port::Pin
				{
				public:
					explicit		Pin(modules::Gpio::Port& port,
								    uint8_t pin_number);

					virtual void		setAsInput(void);
					virtual void 		setAsOutput(void);
					virtual void		set(bool b);
					virtual bool		get(void) const;
					virtual void		toggle(void);

				private:
					Gpio::Port&		port_;
					const uint8_t		pin_bit_;
				};

				//------------------------------------------------------------------
private:
				template<volatile uint8_t& T_DIR,
				volatile uint8_t& T_OUT,
				volatile uint8_t& T_IN,
				volatile uint8_t& T_REN>
				class Port : public yahal::mcu::modules::Gpio::Port
				{
				private:
						class Configuration
						{
							class PullUpResistor
							{
								void disable(uint8_t mask=0xFF);
								void high(uint8_t mask=0xFF);
								void low(uint8_t mask=0xFF);
							};
						public:
							PullUpResistor pullup;
						};

				public:
					virtual void		setAsInput(uint8_t mask=0xFF);
					virtual void		setAsOutput(uint8_t mask=0xFF);
					virtual void		set(uint8_t value, uint8_t mask=0xFF);
					virtual void		toggle(uint8_t mask=0xFF);
					virtual uint8_t		get(uint8_t mask=0xFF)const;
					virtual Gpio::Pin&	pin(uint8_t pin_number);
					Configuration 		config;
				};

				typedef Port<P1DIR,P1OUT,P1IN,P1REN> Port1;
				typedef Port<P2DIR,P2OUT,P2IN,P2REN> Port2;
				typedef Port<P3DIR,P3OUT,P3IN,P3REN> Port3;
				typedef Port<P4DIR,P4OUT,P4IN,P4REN> Port4;
				typedef Port<P5DIR,P5OUT,P5IN,P5REN> Port5;
				typedef Port<P6DIR,P6OUT,P6IN,P6REN> Port6;

				//------------------------------------------------------------------
private:
				Gpio(void);
				friend class cool::pattern::creational::Singleton<Gpio>;

public:
	virtual
	modules::Gpio::Port& 	port(uint8_t portNumber);

private:
	Port1			port1_;
	Port2			port2_;
	Port3			port3_;
	Port4			port4_;
	Port5			port5_;
	Port6			port6_;
};





/*
class Port : public yahal::mcu::modules::Gpio::Port
				{
				private:
						class Configuration
						{
							class PullUpResistor
							{
								void disable(uint8_t mask=0xFF);
								void high(uint8_t mask=0xFF);
								void low(uint8_t mask=0xFF);
							};
						public:
							PullUpResistor pullup;
						};

						struct Registers
						{
							Registers(volatile uint8_t& dir,
								  volatile uint8_t& out,
								  volatile uint8_t& in,
								  volatile uint8_t& ren) :
								dir(dir),
								out(out),
								in(in),
								ren(ren)
							{}

							volatile uint8_t& dir;
							volatile uint8_t& out;
							volatile uint8_t& in;
							volatile uint8_t& ren;
						};

						class Pin : public yahal::mcu::modules::Gpio::Port::Pin
						{
							virtual void	setAsInput(void) {}
							virtual void 	setAsOutput(void) {}
							virtual void	set(bool b){}
							virtual bool	get(void) const {}
							virtual void	toggle(void) {}
						};

						// -------------------------------------------------
				public:
								Port(uint8_t port_number) : port_(port_number-1) {}

					virtual void		setAsInput(uint8_t mask=0xFF);
					virtual void		setAsOutput(uint8_t mask=0xFF);
					virtual void		set(uint8_t value, uint8_t mask=0xFF);
					virtual void		toggle(uint8_t mask=0xFF);
					virtual uint8_t		get(uint8_t mask=0xFF)const;
					virtual Pin&		pin(uint8_t pin_number);
					//Configuration 	config;

				private:
					static Registers	reg[6];
					const uint8_t		port_;
					Pin			pin0_;
				};


				//------------------------------------------------------------------
private:
				// SINGLETON
				Gpio(void);
	friend class		cool::pattern::creational::Singleton<Gpio>;

public:
	virtual Port& 		port(uint8_t portNumber);

private:
	Port			port1_, port2_, port3_, port4_, port5_, port6_;
 */


/*
 * class yahal::mcu::modules::Gpio::Port::Pin
{
public:
	explicit		Pin(yahal::mcu::modules::Gpio::Port& port, uint8_t pin_number):
					port_(port),
					pin_bit_(1<<pin_number) ///< If pin_number greate than 7, then, pin_bit_ = 0x00
				{}


				// CONFIGURATION
	void			input(void);
	void 			output(void);

				// CONTROL
	inline void		set(bool b);
	inline bool		get(void) const;
	inline bool		getOutput(void) const;
	inline void		toggle(void);

private:
				// PRIVATE VARIABLES
	Gpio::Port&		port_;
	const uint8_t		pin_bit_;
};*/



/* ---------------------------------------------------------------------------------------------- */
#endif // YAHAL_MCU_MSP430F5309_ENABLE_GPIO
#endif // __YAHAL_MCU_MSP430F5309_GPIO_HPP_INCLUDED__
