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
#include "../../../modules/irq/isr_provider.hpp"
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
template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
class yahal::mcu::targets::msp430f5309::Port :
	public yahal::mcu::modules::Port,
	public yahal::mcu::modules::IsrProvider<yahal::mcu::targets::msp430f5309::irq::Port::Type>
{
	/// @brief Configure HW port as input.
static inline void 	setAsInput_(uint8_t mask)
	{
		T_DIR &= ~mask;
	}

	/// @brief Configure HW port as output.
static inline  void 	setAsOutput_(uint8_t mask)
	{
		T_DIR |= mask;
		configure(Pullup::DISABLE,mask);
	}

	/// Write value to HW port (only to masked bits).
static inline void 	set_(uint8_t value, uint8_t mask)
	{
		T_OUT = yahal::utility::data::setMasked(T_OUT, value, mask);
	}

	/// @brief Read HW port (only masked bits).
	/// Reads input buffer for bits configured as input.
	/// Reads output buffer for bits configured as output.
static inline uint8_t	get_(uint8_t mask)
	{
		uint8_t input = ~T_DIR & T_IN;
		uint8_t output = T_DIR & T_OUT;
		return (input|output) & mask;
	}

	/// Toggle HW bits (only masked bits)
static inline void 	toggle_(uint8_t mask)
	{
		T_OUT ^= mask;
	}



	/// This class serves as entry point to access Port's private configuration function.
	/// By returning a instance of this class to the user configuration can be done with
	/// explicit and verbose functions.
	/// Configuration is performed using a bit mask, only masked bits will be affected.
	class Configuration
	{
	public:
		class PullupResistor
		{
		public:
			void	disable(uint8_t mask=0xFF){ Port::configure(Pullup::DISABLE,mask); }
			void 	high(uint8_t mask=0xFF)   { Port::configure(Pullup::HIGH,mask); }
			void 	low(uint8_t mask=0xFF)    { Port::configure(Pullup::LOW,mask); }
		}pullup;
	};
	

	/// The Pin class represents a single pin on the port.
	/// It must be instantiated with a mask of its position.
	/// Pin contains its own configuration subclass, which uses pin's bit-mask.
	class Pin : public yahal::mcu::modules::Port::Pin
	{
		class Configuration
		{
		public:
			class PullupResistor
			{
			public:
				void 	disable() { Port::configure(Pullup::DISABLE,mask_); }
				void 	high()	  { Port::configure(Pullup::HIGH,mask_); }
				void 	low()	  { Port::configure(Pullup::LOW,mask_); }

					// CONSTRUCTOR
					PullupResistor(const uint8_t& mask) :
						mask_(mask)
					{}

			private:
				const uint8_t&	mask_;

			}pullup;

			Configuration(const uint8_t& mask) :
				pullup(mask)
			{}
		};

		//----------------------------------------------------------------------------------

	public:
				Pin(uint8_t pin_number) :
					pin_bit_(0x01<<pin_number),
					config(pin_bit_)
				{}

		virtual void	setAsInput(void) { Port::setAsInput_(pin_bit_); }
		virtual void	setAsOutput(void){ Port::setAsOutput_(pin_bit_); }
		virtual void	set(bool b)	 { Port::set_(pin_bit_, pin_bit_); }
		virtual bool	get(void) const  { return Port::get_(pin_bit_); }
		virtual void	toggle(void)	 { Port::toggle_(pin_bit_); }

		Configuration	config;


	private:
		const uint8_t 	pin_bit_;
	};

	//------------------------------------------------------------------------------------------

	/*template<typename T>
	class PinAlias : public yahal::mcu::modules::Port::Pin
	{
	public:
		PinAlias(T& reference) :
			reference_(reference)
		{}

		inline operator T&(void)
		{
			return reference_;
		}

		inline virtual void	setAsInput(void) { reference_.T::setAsInput(); }
		inline virtual void	setAsOutput(void){ reference_.T::setAsOutput(); }
		inline virtual void	set(bool b)	 { reference_.T::set(b); }
		inline virtual bool	get(void) const  { return reference_.T::get(); }
		inline virtual void	toggle(void)	 { reference_.T::toggle(); }


	private:
		T& reference_;
	};

	*/

	template<uint8_t T_PIN_MASK>
	class PinT// : public yahal::mcu::modules::Port::Pin
	{
	public:
		static void	setAsInput(void) { Port::setAsInput_(T_PIN_MASK); }
		static void	setAsOutput(void){ Port::setAsOutput_(T_PIN_MASK); }
		static void	set(bool b)	 { Port::set_(T_PIN_MASK, T_PIN_MASK); }
		static bool	get(void)  	 { return Port::get_(T_PIN_MASK); }
		static void	toggle(void)	 { Port::toggle_(T_PIN_MASK); }
	};

	typedef PinT<0b00000001>	Pin0;
	typedef PinT<0b00000010>	Pin1;
	typedef PinT<0b00000100>	Pin2;
	typedef PinT<0b00001000>	Pin3;
	typedef PinT<0b00010000>	Pin4;
	typedef PinT<0b00100000>	Pin5;
	typedef PinT<0b01000000>	Pin6;
	typedef PinT<0b10000000>	Pin7;
	typedef PinT<0b00000000>	PinEmpty;

	//------------------------------------------------------------------------------------------
private:

	friend class		yahal::mcu::targets::msp430f5309::Msp430f5309;
				Port(void)		{}


public:
	virtual void		setAsInput(uint8_t mask = 0xFF)		{ setAsInput_(mask); }
	virtual void 		setAsOutput(uint8_t mask = 0xFF)	{ setAsOutput_(mask); }
	virtual void 		set(uint8_t value, uint8_t mask = 0xFF) { set_(value,mask); }
	virtual uint8_t		get(uint8_t mask = 0xFF) const		{ return get_(mask); }
	virtual void 		toggle(uint8_t mask = 0xFF)		{ toggle_(mask); }

	virtual void		isr(irq::Port::Type)	{}
	virtual void 		enableIrq(void)		{}
	virtual void 		disableIrq(void)	{}


				/// Returns reference to specified pin (from 0 - 7).
				/// Returns empty instance if pin does not exist.
	/*virtual Pin&		pin(uint8_t pin_number)
				{
					DEBUG_ASSERT(pin_number <= 7);

					switch(pin_number)
					{
					case 0: return pin0_;
					case 1: return pin1_;
					case 2: return pin2_;
					case 3: return pin3_;
					case 4: return pin4_;
					case 5: return pin5_;
					case 6: return pin6_;
					case 7: return pin7_;
					default:return empty_pin_;
					}
				}

	PinAlias<Pin>		pin_(uint8_t pin_number)
				{
					DEBUG_ASSERT(pin_number <= 7);

					switch(pin_number)
					{
					case 0: return pin0_;
					case 1: return pin1_;
					case 2: return pin2_;
					case 3: return pin3_;
					case 4: return pin4_;
					case 5: return pin5_;
					case 6: return pin6_;
					case 7: return pin7_;
					default:return empty_pin_;
					}
				}*/


				/// Access to configuration.
	Configuration		config;



private:


				/// @brief Configure port (only masked bits).
				/// Pullup configuration only affect pins configured for input.
				/// @param pullup (disabled/high/low).
	static void		configure(Pullup::Type pullup, uint8_t mask)
				{
					// Enable pullup only on input pins
					uint8_t input_pins = ~T_DIR & mask;

					switch(pullup)
					{
					case Pullup::HIGH:
						T_REN |= input_pins;	// Enable resistor
						T_OUT |= input_pins;	// Set as pull-UP
						break;
					case Pullup::LOW:
						T_REN |= input_pins;	// Enable resistor
						T_OUT &= ~input_pins;	// Set as pull-DOWN
						break;
					default:
					case Pullup::DISABLE:
						T_REN &= ~mask;
						break;
					}
				}

public:
	static Pin0		pin0;
	static Pin1		pin1;
	static Pin2		pin2;
	static Pin3		pin3;
	static Pin4		pin4;
	static Pin5		pin5;
	static Pin6		pin6;
	static Pin7		pin7;

/*
//private:
public:
	static Pin		pin0_;
	static Pin		pin1_;
	static Pin		pin2_;
	static Pin		pin3_;
	static Pin		pin4_;
	static Pin		pin5_;
	static Pin		pin6_;
	static Pin		pin7_;*/
};



/* ---------------------------------------------------------------------------------------------- */

/*


template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin0_(0);

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin1_(1);

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin2_(2);

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin3_(3);

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin4_(4);

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin5_(5);

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin6_(6);

template<volatile uint8_t& T_DIR,
	 volatile uint8_t& T_OUT,
	 volatile uint8_t& T_IN,
	 volatile uint8_t& T_REN>
yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::Pin
	yahal::mcu::targets::msp430f5309::Port<T_DIR,T_OUT,T_IN,T_REN>::pin7_(7);*/


/* ---------------------------------------------------------------------------------------------- */
#endif	// YAHAL_MCU_MSP430F5309_ENABLE_PORT#
#endif	// __YAHAL_MCU_MSP430F5309_PORT_HPP_INCLUDED__
