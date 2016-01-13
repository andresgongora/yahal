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




#ifndef __M430F2132_I2C_MASTER_HPP_INCLUDED__
#define __M430F2132_I2C_MASTER_HPP_INCLUDED__


/* ---------------------------------------------------------------------------------------------- */
#include "hal/mcu/devices/msp430f2132/msp430f2132.hpp"
#ifdef __MSP430F2132_I2C_MASTER_ENABLED__

#include "hal/mcu/virtual/i2c/i2c_master.hpp"
#include "hal/utility/publish_subscribe.hpp"


/* ============================================================================================== */
 *	DECLARATION::I2C_MASTER
 * ============================================================================================== */

class hal::uc::msp430f2132::I2c_master:	public hal::uc::I2CMaster,
					public hal::utility::Subscriber<hal::uc::Irq::I2C::Type>
{
public:
				// INITIALIZATION
	bool			init(uint8_t ownAddress = 0);


public:

	void			start(uint8_t slaveAddress, DIRECTION::Type direction);
	void			stop(void);
//	void			acknowledge(bool ack);
	void			writeBufferTX(uint8_t byte);
	uint8_t			readBufferRX(void);
	void			awaitTransmissionEnd(void);

	void			notify(hal::uc::Irq::I2C::Type message);
};



/* ============================================================================================== */
 *	hal::uc::msp430f2132::I2c_master :: GLOBAL VARIABLE
 * ============================================================================================== */

namespace hal{namespace uc{namespace msp430f2132{
	extern hal::uc::msp430f2132::I2c_master i2c_master;
}}}


/* ---------------------------------------------------------------------------------------------- */
#endif // __MSP430F2132_I2C_MASTER_ENABLED__
#endif // __M430F2132_I2C_MASTER_HPP_INCLUDED__
