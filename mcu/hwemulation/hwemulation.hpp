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



#ifndef __SOFTWARE_HPP_INCLUDED__
#define __SOFTWARE_HPP_INCLUDED__






// LOAD EMULATED MODULES
#include "i2c/i2c_master.hpp"


// LOAD CONFIGURATION
#include "../config/hwemulation/hwemulation_config.hpp"




namespace yahal{ namespace mcu{ namespace hwemulation {
	class HWEmulation;
}}}


/* =================================================================================================
	INSTANCES
================================================================================================= */

namespace yahal{ namespace mcu{

#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
	static hwemulation::I2CMaster		\
	YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1	\
	(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1);
#endif
#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
	static hwemulation::I2CMaster		\
	YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2	\
	(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2);
#endif
#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
	static hwemulation::I2CMaster		\
	YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3	\
	(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3);
#endif


}} // namespace yahal::mcu



/* =================================================================================================
	TARGET INITIALIZATION
================================================================================================= */

namespace yahal{ namespace mcu{ namespace details{


void initHwemulation(void)
{
	// I2C
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1.init();
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2.init();
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
		YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3.init();
	#endif
}




}}} // Namespace yahal::mcu::details


class yahal::mcu::hwemulation::HWEmulation
{
	/*
public:
	HWEmulation(void) :
			//I2C
		#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
		&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
			YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1
			(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1);
		#endif
		#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
		&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
			YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2
			(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2);
		#endif
		#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
		&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
			YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3
			(hwemulation::config::YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3);
		#endif

		constructor_guard_(NULL) {
	}

	// -----------------------------------------------------------------------------------------

	void init(void) {
		// I2C
		#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
		&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
			YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1.init();
		#endif
		#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
		&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
			YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2.init();
		#endif
		#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
		&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
			YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3.init();
		#endif
	}

	// -----------------------------------------------------------------------------------------

	// I2C
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1)
		yahal::mcu::hwemulation::I2CMaster YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME1;
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2)
		yahal::mcu::hwemulation::I2CMaster YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME2;
	#endif
	#if	YAHAL_MCU_HWEMULATION_I2C_MASTER_INSTANTIATE == true	\
	&&	defined(YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3)
		yahal::mcu::hwemulation::I2CMaster YAHAL_MCU_HWEMULATION_I2C_MASTER_NAME3;
	#endif

	// -----------------------------------------------------------------------------------------

private:
	const int constructor_guard_;
	*/
};


/* ---------------------------------------------------------------------------------------------- */
#endif // __SOFTWARE_HPP_INCLUDED__
