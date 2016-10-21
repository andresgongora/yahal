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

#ifndef __YAHAL_MCU_MODULES_NAMESPACE_HPP_INCLUDED__
#define __YAHAL_MCU_MODULES_NAMESPACE_HPP_INCLUDED__


#include <stdint.h>



namespace yahal{ namespace mcu{ namespace modules{

	// MODULES
	class BaseModule;

	class Clk;
	class Port;
	class Wdt;
	class I2CMaster;
	class I2CMultimaster;
	class I2CSlave;

	template<typename T_SIZE = void> class Timer;
	typedef Timer<uint8_t>	Timer8;
	typedef Timer<uint16_t>	Timer16;
	typedef Timer<uint32_t>	Timer32;
	typedef Timer<uint64_t>	Timer64;

	template<typename T_IRQ> class IrqSource;
	template<typename T_IRQ> class IrqHandler;
	template<typename T_IRQ> class IrqForwarder;

	// DETAILS
	namespace details{




		class GpioConfiguration;
		class I2CCommon;
		class Timer;


	}
}}}



/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_MCU_MODULES_NAMESPACE_HPP_INCLUDED__
