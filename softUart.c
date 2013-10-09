#include <avr/io.h>
#include <avr/interrupt.h>
#include "softUart.h"

static uint8_t gUartData;
static uint8_t gNewData = 0;

void softUartInit(void)
{
    UART_RX_DDR  &= ~(1<<UART_RX_BIT);
    UART_RX_PORT |=  (1<<UART_RX_BIT);

    TCCR1  = (1<<CTC1);
    TCCR1 |= 2;         /* Clock prescaler CK/2 */
    OCR1C  = 208/4;     /* 1MHz/2/208 = 2.40384615kHz = 2400baud */
    OCR1A  = 1;         /* 1MHz/2/208 = 2.40384615kHz = 2400baud */
    TIMSK |= (1<<OCIE1A);
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
            }
            break;

        case BYTE:
            if (!(clkCount % 4))
            {
                gUartData = gUartData >> 1;
                if (RX_STATE())
                    gUartData |= (1<<7);
                else
                    gUartData &= ~(1<<7);

                if (clkCount == 8*4)
                {
                    gNewData = 1;
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
