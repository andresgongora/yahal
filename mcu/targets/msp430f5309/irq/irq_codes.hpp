// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------+-----------------------------------+
	|                                                                       |
	|             Yet Another Hardware Abstraction Layer (YAHAL)            |
	|                https://github.com/andresgongora/yahal                 |
	|                                                                       |
	|                                                                       |
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file. |
	| Machine Perception and Intelligent Robotics (MAPIR),                  |
	| University of Malaga. <http://mapir.isa.uma.es>                       |
	|                                                                       |
	| This program is free software: you can redistribute it and/or modify  |
	| it under the terms of the GNU General Public License as published by  |
	| the Free Software Foundation, either version 3 of the License, or     |
	| (at your option) any later version.                                   |
	|                                                                       |
	| This program is distributed in the hope that it will be useful,       |
	| but WITHOUT ANY WARRANTY; without even the implied warranty of        |
	| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
	| GNU General Public License for more details.                          |
	|                                                                       |
	| You should have received a copy of the GNU General Public License     |
	| along with this program. If not, see <http://www.gnu.org/licenses/>.  |
	|                                                                       |
	+-----------------------------------------------------------------------+ */


#ifndef __YAHAL_MCU_MSP430F5309_IRQ_CODES_HPP_INCLUDED__
#define __YAHAL_MCU_MSP430F5309_IRQ_CODES_HPP_INCLUDED__


#include "../../../config/config.hpp"
#if YAHAL_MCU_TARGET == YAHAL_MCU_MSP430F5309


namespace yahal{
namespace mcu{
namespace targets{
namespace msp430f5309{
namespace irq{
/* ---------------------------------------------------------------------------------------------- */


struct Port{ enum Type{
	NONE,
};};



/* ---------------------------------------------------------------------------------------------- */
}	// namespace irq
}	// namespace msp430f5309
}	// namespace targets
}	// namespace mcu
}	// namespace yahal
#endif	// YAHAL_MCU_DEVICE == YAHAL_MCU_MSP430F5309
#endif 	// __YAHAL_MCU_MSP430F5309_IRQ_CODES_HPP_INCLUDED__

