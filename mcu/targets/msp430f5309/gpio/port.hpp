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


#ifndef __YAHAL_MCU_MSP430F5309_PORT_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_PORT_HPP_INCLUDED__


#include "../../../config/targets/msp430f5309.hpp"
#if	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT1 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT2 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT3 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT4 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT5 ) || \
	defined( YAHAL_MCU_MSP430F5309_ENABLE_PORT6 )


#include <stdint.h>
#include <msp430f5309.h>
#include "../msp430f5309_namespace.hpp"
#include "../irq/irq_codes.hpp"
#include "../../../modules/gpio/port.hpp"
#include "../../../modules/irq/irq_handler.hpp"
#include "../../../../utility/data/mask.hpp"
#include "../../../../error/debug_assert.hpp"


namespace{

	/// For convenience, use names for pull-up/down resistors.
	struct Pullup{ enum Type{
		HIGH,
		LOW,
		DISABLE
	};};
}

//TODO: MOVE THIS OUT
#define SFR_8	volatile uint8_t
#define SFR_16	volatile uint8_t
#define SFR_32	volatile uint8_t


/***********************************************************************************************//**
 * @brief	MSP430F5309 templated port class
 *
 * @tparam	T_DIR	direction register. 0 = intput, 1 = output
 * @tparam	T_OUT	output buffer register
 * @tparam	T_IN	input buffer register
 * @tparam	T_REN	pull-up/pull-down control register
 *
 * @note	Some functions are static in order to give the Pin class access to them without
 *		need for a pointer/instance/reference to Port.
 **************************************************************************************************/
template<SFR_8& T_DIR, SFR_8& T_OUT, SFR_8& T_IN, SFR_8& T_REN>
class yahal::mcu::targets::msp430f5309::hw::Port
{
public:
				class Configuration;

				template<int T_PIN>
				class Pin;


	static void		init(void)
				{}

				/// Write value to HW port (only to masked bits).
	static void 		set(uint8_t value, uint8_t mask)
				{
					T_OUT = yahal::utility::data::setMasked(T_OUT, value, mask);
				}

				/// @brief Read HW port (only masked bits).
				/// Reads input buffer for bits configured as input.
				/// Reads output buffer for bits configured as output.
	static uint8_t 		get(uint8_t mask)
				{
					uint8_t input = ~T_DIR & T_IN;
					uint8_t output = T_DIR & T_OUT;
					return (input | output) & mask;
				}

				/// Toggle HW bits (only masked bits)
	static void 		toggle(uint8_t mask)
				{
					T_OUT ^= mask;
				}


				/// @brief Configure HW port as input.
	static void 		setAsInput(uint8_t mask)
				{
					T_DIR &= ~mask;
				}

				/// @brief Configure HW port as output.
	static void 		setAsOutput(uint8_t mask)
				{
					T_DIR |= mask;
//					Port::Configuration::Pullup::disable(mask);
				}




};


template<SFR_8& T_DIR, SFR_8& T_OUT, SFR_8& T_IN, SFR_8& T_REN>
class yahal::mcu::targets::msp430f5309::hw::Port<T_DIR,T_OUT,T_IN,T_REN>::Configuration
{
public:
	class Pullup
	{
	public:
		static void high(uint8_t mask=0xFF)
		{
			uint8_t input_pins = ~T_DIR & mask;
			T_REN |= input_pins;	// Enable up resistor
			T_OUT |= input_pins;// for input pins
		}

		static void low(uint8_t mask=0xFF)
		{
			uint8_t input_pins = ~T_DIR & mask;
			T_REN |= input_pins;	// Enable down resistor
			T_OUT &= ~input_pins;// for input pins
		}

		static void disable(uint8_t mask=0xFF)
		{
			T_REN &= ~mask;
		}
	};

public:
	Pullup	pullup;
};


template<SFR_8& T_DIR, SFR_8& T_OUT, SFR_8& T_IN, SFR_8& T_REN>
template<int T_PIN>
class yahal::mcu::targets::msp430f5309::hw::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
{
public:
	static void 	set(bool b)		{ Port::set(0xFF, (1<<T_PIN)); }
	static bool 	get(void)		{ return Port::get(1<<T_PIN); }
	static void 	toggle(void)		{ Port::toggle(1<<T_PIN); }
	static void 	setAsInput(void)	{ Port::setAsInput(1<<T_PIN); }
	static void 	setAsOutput(void)	{ Port::setAsOutput(1<<T_PIN); }



	class Configuration
	{
	public:
		class Pullup
		{
		public:
			void high()	{ Port::Configuration::Pullup::high(1<<T_PIN); }
			void low()	{ Port::Configuration::Pullup::low(1<<T_PIN); }
			void disable()	{ Port::Configuration::Pullup::disable(1<<T_PIN); }
		};

	public:
		Pullup	pullup;
	};


};




template<typename T_PORT, unsigned int T_WIDTH>
class PortManager;


template<typename T_PORT>
class PortManager<T_PORT,0> :
	public yahal::mcu::modules::Port
{
//private:
public:				PortManager(void)	{T_PORT::init();}


public:
	virtual void		set(uint8_t value, uint8_t mask=0xFF)	{ T_PORT::set(value,mask); }
	virtual uint8_t		get(uint8_t mask=0xFF) const 		{ return T_PORT::get(mask);}
	virtual void		toggle(uint8_t mask=0xFF)		{ T_PORT::toggle(mask); }

	virtual void		setAsInput(uint8_t mask=0xFF)		{ T_PORT::setAsInput(mask);}
	virtual void		setAsOutput(uint8_t mask=0xFF)		{ T_PORT::setAsOutput(mask);}


	template<int T_PIN>
	class Pin :
		public yahal::mcu::modules::Port::Pin
	{
	public:
		virtual void	set(bool b)	{ T_PORT::template Pin<T_PIN>::set(b); }
		virtual bool	get(void) const { return T_PORT::template Pin<T_PIN>::get(); }
		virtual void	toggle(void)	{ T_PORT::template Pin<T_PIN>::toggle(); }

		virtual void	setAsInput(void){ T_PORT::template Pin<T_PIN>::setAsInput(); }
		virtual void	setAsOutput(void){ T_PORT::template Pin<T_PIN>::setAsOutput(); }

		typename T_PORT::template Pin<T_PIN>::Configuration cfg;
	};


	typename T_PORT::Configuration cfg;
};

template<typename T_PORT>
class PortManager<T_PORT,8> :
	public PortManager<T_PORT,0>
{
public:
	typename PortManager::template Pin<0> pin0;
	typename PortManager::template Pin<1> pin1;
	typename PortManager::template Pin<2> pin2;
	typename PortManager::template Pin<3> pin3;
	typename PortManager::template Pin<4> pin4;
	typename PortManager::template Pin<5> pin5;
	typename PortManager::template Pin<6> pin6;
	typename PortManager::template Pin<7> pin7;

};


typedef PortManager<yahal::mcu::targets::msp430f5309::hw::Port<P1DIR, P1OUT, P1IN, P1REN>, 8> Portazo1;



/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_MSP430F5309_ENABLE_PORT#
#endif	// __YAHAL_MCU_MSP430F5309_PORT_HPP_INCLUDED__
