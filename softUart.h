/**
 * \file   softUart.h
 * \author Tuomas Nylund
 * \brief  Header for uart receiver implemented using timer interrupt
 */
/* This program is free software: you can redistribute it and/or modify it under
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
 */

#ifndef _SOFTUART_H_
#define _SOFTUART_H_

#define UART_RX_PORT PORTB /**< Port register of the UART RX pin */
#define UART_RX_DDR  DDRB  /**< Data direction register of the UART RX pin */
#define UART_RX_PIN  PINB  /**< Port in register of the UART RX pin */
#define UART_RX_BIT  PB4   /**< The bit of the UART RX pin */

#define RX_STATE()   (UART_RX_PIN & (1<<UART_RX_BIT)) /**< Macro to read RX pin */

/**
 * \brief  UART states
 */
typedef enum
{
    WAIT_FOR_START_BIT, /**< Waiting for start bit */
    BYTE,               /**< Currently receiving a byte */
    STOP_BIT            /**< Waiting for stop bit to end */
} E_softUartStates;

/**
 * \brief  Initialize UART and start the RX
 */
void    softUartInit(void);

/**
 * \brief  Check if new character has been received
 *
 * \return (1) if new character has been received, otherwise returns 0
 */
uint8_t softUartNewChar(void);

/**
 * \brief  Read most recent received character
 *
 * \return Most recent received character
 */
uint8_t softUartGetChar(void);

#endif /* _SOFTUART_H_ */
