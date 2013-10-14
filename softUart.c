/*******************************************************************************
* \file   softUart.c
* \brief  Source file for uart receiver implemented using timer interrupt
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "softUart.h"

static uint8_t gUartData;
static uint8_t gNewData = 0;

void softUartInit(void)
{
    UART_RX_DDR  &= ~(1<<UART_RX_BIT);
    UART_RX_PORT |=  (1<<UART_RX_BIT);

    TCCR1  = (1<<CTC1);   /* Clear timer on compare with OCR1C */
    TCCR1 |= 2;           /* Clock prescaler CK/2 */
    OCR1C  = 208/4;       /* 1MHz/2/208 = 2.40384615kHz = 2400baud. sampling 4 times/bit */
    OCR1A  = 1;           /* No interrupt available on OCR1A, so we are using this */
    TIMSK |= (1<<OCIE1A); /* Enable interrupt */
}

uint8_t softUartNewChar(void)
{
    return gNewData;
}
uint8_t softUartGetChar(void)
{
    gNewData = 0;
    return gUartData;
}

ISR(TIMER1_COMPA_vect)
{
    static uint8_t state    = WAIT_FOR_START_BIT;
    static uint8_t clkCount = 0;
    static uint8_t data;

    clkCount++;

    switch(state)
    {
        case WAIT_FOR_START_BIT:
            if (RX_STATE())
                clkCount = 0;

            if (clkCount == 2)
            {
                state = BYTE;
                clkCount = 0;
                data = 0;
            }
            break;

        case BYTE:
            if (!(clkCount % 4))
            {
                data = data >> 1;
                if (RX_STATE())
                    data |= (1<<7);

                if (clkCount == 8*4)
                {
                    gNewData = 1;
                    gUartData = data;

                    state = STOP_BIT;
                    clkCount = 0;
                }
            }
            break;

        case STOP_BIT:
            if (clkCount == 4)
                state = WAIT_FOR_START_BIT;
            break;
    }
}
