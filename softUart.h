/*******************************************************************************
* \file   softUart.h
* \brief  Header for uart receiver implemented using timer interrupt
* \author Tuomas Nylund
* 
* This program is free software: you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation, either version 3 of the License, or (at your option) any later
* version.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
* details.
* 
* You should have received a copy of the GNU General Public License along with
* this program. If not, see <http://www.gnu.org/licenses/>
*******************************************************************************/

#ifndef _SOFTUART_H_
#define _SOFTUART_H_

#define UART_RX_PORT PORTB
#define UART_RX_DDR  DDRB
#define UART_RX_PIN  PINB
#define UART_RX_BIT  PB4

#define RX_STATE()   (UART_RX_PIN & (1<<UART_RX_BIT))

/* 0,1,2,3,4,5,6,7 */

typedef enum
{
    WAIT_FOR_START_BIT,
    BYTE,
    STOP_BIT
} E_softUartStates;

void    softUartInit(void);
uint8_t softUartNewChar(void);
uint8_t softUartGetChar(void);

#endif /* _SOFTUART_H_ */
