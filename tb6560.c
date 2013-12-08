/**
 * \file   tb6560.c
 * \author Tuomas Nylund
 * \brief  Source for tb6560 stepper controller
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "tb6560.h"

/* Global variables */
int16_t gSteps;

/* Static functions */

static void initializeTimer(void)
{
    TCCR1  = (1<<CTC1);   /* Clear timer on compare with OCR1C */
    // TCCR1 |= 8;           /* Clock prescaler CK/64 */
    // OCR1C  = 250;         /* 1MHz/64/250 = 2kHz */
    
    GTCCR |= (1<<COM1B0); /* Toggle the OC1B output line on OCR1B compare*/
    OCR1B  = 1;           /* We need to trigger somewhere */
    TIMSK |= (1<<OCIE1B); /* Enable interrupt */
}

static void enableTimer(void)
{
    TCCR1 |= PRESCALER_VALUE; /* Setting the clock prescaler starts the timer */
}

static void disableTimer(void)
{
    TCCR1 &= PRESCALER_CLEAR_MASK; /* Clearing prescaler stops timer */
}

/* Functions */
void tb6560Init(void)
{
    TB6560_CLK_DDR  |= (1<<TB6560_CLK_BIT);
    TB6560_EN_DDR   |= (1<<TB6560_EN_BIT);
    TB6560_DIR_DDR  |= (1<<TB6560_DIR_BIT);

    initializeTimer();
}

void tb6560SetSpeed(uint8_t speed)
{
    OCR1C = speed;
}

void tb6560SetSteps(int16_t steps)
{
    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        gSteps = steps;

        if (gSteps>0)
        {
            TB6560_DIR_PORT |= (1<<TB6560_DIR_BIT);
        }
        else if (gSteps<0)
        {
            TB6560_DIR_PORT &= ~(1<<TB6560_DIR_BIT);
        }

        if (gSteps)
        {
            enableTimer();
            TB6560_EN_PORT |= (1<<TB6560_EN_BIT); /* Enable TB6560 */
        }
    }
}

int16_t tb6560GetSteps(void)
{
    int16_t retval;
    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        retval = gSteps;
    }
    return retval;
}

ISR(TIMER1_COMPB_vect)
{
    if (gSteps>0)
    {
        gSteps--;
    }
    else if (gSteps<0)
    {
        gSteps++;
    }
    else
    {
        disableTimer();
        TB6560_EN_PORT &= ~(1<<TB6560_EN_BIT); /* Disable TB6560 */
    }
}
