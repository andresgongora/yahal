	/* 	TODO:
	 * 	- 	Error Code global y con indicacion de origen del error y
	 * 		formato legible (pero que sea opcional)
	 *
	 *	-	Dar direccion de I2C_MASTER y opcion a habilitar GENERAL CALL
	 *		en el contrustror virtual, no en la implementacion,
	 *		ya que esto son dos parametros que no dependen del mcu.
	 *
	 *	- 	Prohibir OWNADDRESS = 0x00 en I2C, ya que es la general call address
	 *
	 *	-	En MASTER_I2C: en write poner los punteros a la pila de salida como CONST. No modificamos esos datos
	 *
	 *
	 *	- Target modules are _NOT_ allowed to have public member functions or variables
	 *
	 *	- A�adir patilla a timer A1
	 *
	 *	- Access to RTOS with a service locator pattern. The same goes for the MCU. Check how slow it is because it adds a pointer
	 *
	 *	- Make all empty classes singletons to avoid unnecesary copies of them
	 *
	 *	- Impedir que desde las ISR de mis modulos se puedan llamar funciones del usuario, para evitar que el usuario llame a otra funcion que espere una ISR y se cree un bucle -> tengo que arreglar los publisher subscribers
	 *
	 *	- Para que publisher-subscriber NO dependa de un rtos, hacer que el publisher y subscriber utilicen un tipo de dato que no sea un entero, sino un paquete cuyo valor se puede escribir, pero no es leido hasta que no le toca al hilo correspondiente.
	 *
	 *	- Subscriber: hacer de dos tipos. Un subscriber variable que dependa del modulo abstracto. Por ejemplo un subscriber de tipo TIMER. Este subscriber puede subscribirse a cualquier timer.
	 *	hacer tmb un subscriber tipo MSP::TIMERA1, que cualquier clase que derive de este subscriber automaticamente (y const) quede suscrito al timer correcto. Por tanto requiero de singletons.
	 *
	 *	- Propuesta para singletons: estudiar la posibilidad de usar singletons, pero no exponer que sea singletons fuera de mi libreria. Usar solo como herramienta interna a la que el usuario final no pueda acceder. "Protected static-singleton con friendship"
	 *
	 *	- Los managers no deben aceptar por referencia, deben HEREDAR (private) del modulo que deben controlar. Esto es para que puedan sobreescribir la funcion ISR con al suya propia, y evitarse el overhead de ser un subscriptor. Tambien me ahorra crear una instancia del modulo que de todas formas va a ser managed. Usar CRTP
	 *
	 *
	 *		mcu.port1.pin6 = 1;
			mcu.port1.pin6 = 0;
			if(mcu.port1.pin6 == true);  additionally to set and get
	 *
	 *
	*/


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


#ifndef __YAHAL_MCU_HPP_INCLUDED__
#define __YAHAL_MCU_HPP_INCLUDED__


#include "config/config.hpp"
#include "modules/modules.hpp"
#include "targets/targets.hpp"
//#include "hwemulation/hwemulation.hpp"
#include "targets/empty/empty.hpp"


namespace yahal{
namespace mcu{
/* ---------------------------------------------------------------------------------------------- */



/***********************************************************************************************//**
 * @brief
 **************************************************************************************************/
class Mcu :
	public yahal::mcu::Target,
	public cool::pattern::creational::Singleton<Mcu>
{
public:
	bool			init(void);



private:
	friend class		cool::pattern::creational::Singleton<Mcu>;
				Mcu(void);
};



/* ---------------------------------------------------------------------------------------------- */
}	// namespace mcu
}	// namespace yahal
#endif	// __YAHAL_MCU_HPP_INCLUDED__
