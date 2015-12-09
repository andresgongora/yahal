// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2005-2015, Individual contributors, see AUTHORS file 	|
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




#ifndef __UART_HPP_INCLUDED__
#define __UART_HPP_INCLUDED__


/** --- INCLUDE -------------------------------------------------------------------------------- **/
#include "hal/hal_namespace.hpp"
#include "hal/error/object_status.hpp"
#include "hal/std/messagestack.hpp"
#include <string>


/** --- DEFINE --------------------------------------------------------------------------------- **/
#define UART_ENABLE_PARITY 		1
#define UART_DISABLE_PARITY		0
#define UART_ODD_PARITY			0
#define UART_EVEN_PARITY		1
#define	UART_LSB_FIRST			0
#define UART_MSB_FIRST			1
#define	UART_7_BIT			0
#define	UART_8_BIT			1
#define UART_1_STOP_BIT			0
#define UART_2_STOP_BIT			1
#define UART_SYNC_MODE			1
#define UART_ASYNC_MODE			0

#define UART_BR_9600			9600
#define UART_BR_115200			115200

#define UART_STACK_TX_SIZE		16
#define UART_STACK_RX_SIZE		16

//#define _UART_USE_BLOCKING_TX		// Calling "write" does not return until TX complete



/**MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 **	DECLARATION
 WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW**/

/** ===	UART =================================================================================== **/

class HAL::MCU::Uart : public error::ObjectStatus
{
public:
				// CONSTRUCTOR
				Uart(void) :	flagTXEnabled(0),
						flagRXEnabled(0),
						functionRX_(0) {}


				// INITIALIZATION
	virtual bool		init(	uint32_t baudrate 	= UART_BR_9600,
					bool useSyncMode 	= UART_ASYNC_MODE,
					bool useTwoStopBits	= UART_1_STOP_BIT,
					bool use7Bit		= UART_8_BIT,
					bool setMSBFirst	= UART_MSB_FIRST,
					bool enableParity	= UART_DISABLE_PARITY,
					bool oddParity 		= UART_ODD_PARITY) = 0;


				// WRITE
	bool			write(uint8_t* data, uint8_t len);
	bool			write(char* data, uint8_t len);
	bool			write(const char* data, uint8_t len);
	bool			write(const char* data);
	bool			write(uint8_t& data);
	bool			write(char& data);
	bool			write(std::string& str);



				// READ
	bool			read(uint8_t* data, uint8_t len);
	bool			read(char* data, uint8_t len);
	bool			read(uint8_t& data);
	bool			read(char& data);
//	bool			read(std::string& str);
	uint8_t 		read();


				// IRQ
	void			isrTX(void);
	void			isrRX(void);


				// AUTOMATIC RX
	void			enableCallOnRX(void (* functionRX)(uint8_t));
	void			disableCallOnRX(void);
	bool			isCallOnRXEnabled(void) const;


protected:
				// HARDWARE
	virtual void		enableTXIRQ(void) = 0;
	virtual void		enableRXIRQ(void) = 0;
	virtual void		disableTXIRQ(void) = 0;
	virtual void 		disableRXIRQ(void) = 0;
	virtual void		sendByte(uint8_t byteTX) = 0;
	virtual uint8_t		receiveByte(void) = 0;


private:
				// MESSAGE STACK
	std::MessageStack<uint8_t, UART_STACK_TX_SIZE>	stackTX;
	std::MessageStack<uint8_t, UART_STACK_RX_SIZE>	stackRX;


				// TRANSMISSION CONTROL
	void			enableTX(void);
	void			enableRX(void);
	void			disableTX(void);
	void			disableRX(void);
	bool			isTXEnabled(void) const;
	bool			isRXEnabled(void) const;
	bool			flagTXEnabled;
	bool			flagRXEnabled;


				// AUTOMATIC RX
	void 			(* functionRX_)(uint8_t);
	void			callOnRX(uint8_t byteRX);

public:
				// ERROR CODES
	enum 			errorCodes
				{
					noError = 0,
					error_notInitialized,
					error_unableToInitTXMessage,
					error_unableToInitRXMessage,
					error_attemptToCallDisabledCallOnRXFunction,
					errorOther
				};

};


/** ============================================================================================ **/
#endif 	//__UART_HPP_INCLUDED__
