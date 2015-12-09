// 1 TAB = 8 SPACES //

      /**
	*	ID:
	*   EDITED:
	*    AUTOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
	*	|										|
	*	|										|
	*	|										|
	*	+-------------------------------------------------------------------------------+
	*	
	**/

       /*
	* Copyright (C) 2015 Andres Gongora
	* Machine Perception and Intelligent Robotics (MAPIR)
	* University of Malaga (SPAIN)
	* <https://http://mapir.isa.uma.es/mapirwebsite/>
	*
	* This program is free software: you can redistribute it and/or modify
	* it under the terms of the GNU General Public License as published by
	* the Free Software Foundation, either version 3 of the License, or
	* (at your option) any later version.
	*
	* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License
	* along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/

#ifndef __MCU_MSP430F5309_CONFIG_HPP_INCLUDED__
#define __MCU_MSP430F5309_CONFIG_HPP_INCLUDED__


#if MCU_DEVICE == MCU_MSP430F5309



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	CONFIGURATION
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ======================================================================================== CLK **/
//	+---------------------------------------------------------------+
#define	__MCU_MSP430F5309_CLK_ENABLED__	// Comment to disable
//	+---------------------------------------------------------------+

#ifdef	__MCU_MSP430F5309_CLK_ENABLED__
#define __MCU_MSP430F5309_CLK_INSTANCE_NAME__		clk
#define __MCU_MSP430F5309_CLK_FREQUENCY__			1000000
#define __MCU_MSP430F5309_CLK_FREQUENCY2__			20000
#endif



/** ======================================================================================== WDT **/
#define __MCU_MSP430F5309_WDT_ENABLED__	// Comment to disable




/** ======================================================================================= GPIO **/
#define __MCU_MSP430F5309_GPIO_ENABLED__	// Comment to disable






#define __MCU_MSP430F5309_I2C_MASTER_ENABLED__
#define __MCU_MSP430F5309_I2C_MULTIMASTER_ENABLED__
#define __MCU_MSP430F5309_I2C_SLAVE_ENABLED__




//#define __MCU_MSP430F5309_TIMER_ENABLED__



/*
#ifdef	__MSP430F5309_CLK_ENABLED__
	hal::uc::msp430f5309::clk	__MSP430F5309_CLK_INSTANCE_NAME__(
						__MSP430F5309_CLK_FREQUENCY__,
						__MSP430F5309_CLK_FREQUENCY2__
					);
#endif
*/



/** ============================================================================================ **/
#endif // MCU_DEVICE == MCU_MSP430F5309
#endif //__MCU_MSP430F5309_CONFIGHPP_INCLUDED__
