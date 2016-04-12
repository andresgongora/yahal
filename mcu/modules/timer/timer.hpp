// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015 - 2016 - 2016, Individual contributors, see AUTHORS file. |
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


#ifndef __YAHAL_MCU_MODULES_TIMER_16_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_TIMER_16_HPP_INCLUDED__


#include "../modules_namespace.hpp"
#include "../../../utility/oop/publish_subscribe.hpp"


/***********************************************************************************************//**
 * @brief	Enum and constants related to timer modules.
 **************************************************************************************************/
class yahal::mcu::modules::details::Timer
{
public:
/*				class Comparator
				{
				public:
					struct Mode{ enum Type{
						OFF		= 0x00,
						OUTPUT_COMPARE 	= 0x10,
						INPUT_CAPTURE	= 0x20,
					};};
				};

				class OutputCompare
				{
				public:
					struct Mode{ enum Type{
						NONE	= Comparator::Mode::OUTPUT_COMPARE,
						SET,
						RESET,
						SET_RESET,
						RESET_SET,
						TOGGLE,
						TOGGLE_SET,
						TOGGLE_RESET
					};};
				};

				class InputCapture
				{
				public:
					struct Mode{ enum Type{
						NONE	= Comparator::Mode::INPUT_CAPTURE,
					};};
				};

*/
				class Comparator
				{
				public:
					struct Mode
					{
						enum Type{
							OFF,
						};

						struct OutputCompare{ enum Type{
							NONE,
							SET,
							RESET,
							SET_RESET,
							RESET_SET,
							TOGGLE,
							TOGGLE_SET,
							TOGGLE_RESET,
							PWM_THINGY_STUFF
						};} static const OC;

						struct InputCapture{ enum Type{
							NONE,
							OTHER,
						};} static const IC;
					} static const MODE;
				};
};





/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
template<typename T_SIZE>
class yahal::mcu::modules::Timer :
	public yahal::mcu::modules::details::Timer,
	public yahal::utility::oop::Publisher<int>
{
public:
	//			class OutputCompare;
	//			class InputCapture;
				class Comparator;

				//------------------------------------------------------------------
public:
	virtual void		setCount(T_SIZE count) = 0;
	virtual T_SIZE		getCount(void) const = 0;
	virtual Comparator&	comparator(int) = 0;
};



/***********************************************************************************************//**
 * @brief	Void timer.
 **************************************************************************************************/
template<>
class yahal::mcu::modules::Timer<void> :
	public yahal::mcu::modules::details::Timer
{
};



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
/*template<typename T_SIZE>
class yahal::mcu::modules::Timer<T_SIZE>::OutputCompare :
	public yahal::mcu::modules::details::Timer::OutputCompare
{
public:


				//------------------------------------------------------------------
public:
	virtual bool		setMode(OutputCompare::Mode::Type) = 0;
	virtual void 		setComparator(T_SIZE value) = 0;
	virtual T_SIZE		getComparator(void) const = 0;
	virtual bool 		getOutput(void) const = 0;

};*/



/***********************************************************************************************//**
 * @brief
 *
 * Publishes captured counter value on event.
 *
 **************************************************************************************************/
/*template<typename T_SIZE>
class yahal::mcu::modules::Timer<T_SIZE>::InputCapture :
	public yahal::mcu::modules::details::Timer::InputCapture
{
public:
	virtual bool		setMode(InputCapture::Mode::Type) = 0;
};*/



/***********************************************************************************************//**
 * @brief
 *
 * Publishes captured counter value on event.
 *
 **************************************************************************************************/
template<typename T_SIZE>
class yahal::mcu::modules::Timer<T_SIZE>::Comparator :
	public yahal::mcu::modules::details::Timer::Comparator
{
public:
//	virtual bool		setMode(Mode::Type) = 0;
//	virtual bool		setMode(Mode::OutputCompare::Type) = 0;
//	virtual bool		setMode(Mode::InputCapture::Type) = 0;

//	operator 		T_SIZE() = 0;
//	T_SIZE			operator=(T_SIZE) = 0;
	virtual void 		setComparator(T_SIZE value) = 0;
	virtual T_SIZE		getComparator(void) const = 0;
	virtual bool 		getOutput(void) const = 0;
//	virtual bool 		getSignal(void) const = 0;


//	virtual void		getCount(void) = 0;
};



/* ---------------------------------------------------------------------------------------------- */
#endif 	//__YAHAL_MCU_MODULES_TIMER_16_HPP_INCLUDED__
