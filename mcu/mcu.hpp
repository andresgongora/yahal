	/* 	TODO:
	 * 	- 	Error Code global y con indicacion de origen del error y
	 * 		formato legible (pero que sea opcional)
	 *
	 * 	- 	IRQ con publish_subscribe pero con RTOS (cola de mensajes etc)
	 *
	 *	-	Crear una carpeta config, que contiene mcu_config y una subcarpeta
	 *		target_config con la config de cada placa. De esta forma el usuario
	 *		solo debe tocar una carpeta
	 *
	 *	-	Dar direccion de I2C_MASTER y opcion a habilitar GENERAL CALL
	 *		en el contrustror virtual, no en la implementacion,
	 *		ya que esto son dos parametros que no dependen del mcu.
	 *
	 *	- 	Prohibir OWNADDRESS = 0x00 en I2C, ya que es la general call address
	 *
	 *	-	En MASTER_I2C: en write poner los punteros a la pila de salida como CONST. No modificamos esos datos
	 *
	 *	- BASE MODULE: //TODO: Añadir metodo para solicitar dispositivo (mutex), y al hacerlo borrar codigos de error viejos, comprobar que esta inicializado y todo. La interfaz para comprobar la salud de un modulo deberia estar aqui
	 *
	 *	- Cambiar el funcionamiento para imitar el de RTOS. Las clases base de modulos meterlas en el namespace modulos. Y el micro que implemente el chiringuito meterlo debajo de mcu. Pero no se hacer entonces con hwemulation
	 *
	*/


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

#ifndef __YAHAL_MCU_HPP_INCLUDED__
#define __YAHAL_MCU_HPP_INCLUDED__



// LOAD MCU CONFIGURATION
#include "config/mcu_config.hpp"


// LOAD CODE
#include "modules/modules.hpp"
#include "targets/targets.hpp"
#include "hwemulation/hwemulation.hpp"


namespace yahal{ namespace mcu{

	void init(void)
	{
		yahal::mcu::details::initTarget();
		yahal::mcu::details::initHwemulation();
	}

}} // namespace yahal::mcu



/* ---------------------------------------------------------------------------------------------- */
#endif	// __YAHAL_MCU_HPP_INCLUDED__
