// 1 TAB = 8 SPACES //

      /**
	*	ID:	gpio.hpp
	*   EDITED:	06-05-2015
	*    AUTOR:	Andres Gongora
	*
	*	+------ Description: -----------------------------------------------------------+
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


#ifndef __MCU_GENERIC_MODULE_HPP_INCLUDED__
#define __MCU_GENERIC_MODULE_HPP_INCLUDED__


//TODO: Añadir metodo para solicitar dispositivo (mutex), y al hacerlo borrar codigos de error viejos, comprobar que esta inicializado y todo. La interfaz para comprobar la salud de un modulo deberia estar aqui
//TODO: DIvidir init en not-virtual init() y virtual doInit()

/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include <stdint.h>
#include <cstddef>
#include "../error/error_code.hpp"
#include "../utility/noncopyable.hpp"
#include "../rtos/rtos.hpp"



/** --- NAMESPACE ------------------------------------------------------------------------------ **/
namespace mcu{
	class GenericModule;
}



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	MODULE
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

class mcu::GenericModule : public mcu::error::ErrorCode, private mcu::utility::Noncopyable
{
protected:			// CONSTRUCTOR & DESTRUCTOR
				GenericModule(void) : _initialized(false)	{}
	virtual			~GenericModule(void)				{}



public:				// INITILIZATION
	bool			init(void){
					bool success = false;
					setErrorCode(NO_ERROR);
					doInit();
					if(not hasError())
					{
						setInitialized();
						success = true;
					}
					else
					{
						// SET NOT INITIALIZED ERROR CODE!! TODO
					}
					return success;
				}



public:				// STATUS
	bool			isInitialized(void) const{
					return _initialized;
				}

	virtual bool		isHealthy(void) const{
					bool healthy = true;
					healthy &= this->hasError();
					healthy &= isInitialized();
					return healthy;
				}



protected:			// LOCK & UNLOCK MODULE FOR USE
	void			open(void){
					_mutex.lock();
					this->setErrorCode(NO_ERROR);
					if(not isInitialized()){init();}	// Try to init
				}

	void			close(void){
					_mutex.unlock();
				}



protected:			// IMPLEMENT INITIALIZATION
	virtual void		doInit(void) {}



protected:			// STATUS
	void			setInitialized(bool val = true){
					_initialized = val;
				}



private:			// PRIVATE VARIABLES
	bool			_initialized;
	mcu::rtos::Mutex	_mutex;
};


/** ============================================================================================ **/
#endif	// __MCU_GENERIC_MODULE_HPP_INCLUDED__
