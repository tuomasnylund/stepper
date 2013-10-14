/*******************************************************************************
* \file   stepper.c
* \brief  Header for interrupt driven stepper controller
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
#include "stepper.h"

/* Const variables */
const uint8_t C_stepperMasks[] = 
{
    1<<STEPPER_1_BIT, 
    1<<STEPPER_2_BIT, 
    1<<STEPPER_3_BIT, 
    1<<STEPPER_4_BIT
};

/* Static variables */

int8_t gSteps;

/* Static functions */

/* Functions */

void stepperInit(void)
{
    STEPPER_DDR |= STEPPER_MASK;
    TCCR0A |= (1<<WGM01);  /* WGM    = CTC  */
    TCCR0B |= 0b101;       /* CLKDIV = 1024 */
    TIMSK  |= (1<<OCIE0A);
    TIMSK  |= (1<<TOIE0);
    OCR0A = 5;
}

void stepperSetSpeed(uint8_t speed)
{
    OCR0A = speed;
}

void stepperSetSteps(int8_t steps)
{
    gSteps = steps;
}

int8_t stepperGetSteps(void)
{
    return gSteps;
}

/* Interrupts */

ISR(TIMER0_COMPA_vect)
{
    static uint8_t state = 0;

    uint8_t newOutput;

    if ( gSteps )
    {
        newOutput = C_stepperMasks[ state ];

        if ( gSteps > 0 )
        {
            state += 1;
            gSteps--;
        }
        else if ( gSteps < 0 )
        {
            state -= 1;
            gSteps++;
        }
        state %= 4;

        newOutput |= C_stepperMasks[ state ];

        STEPPER_PORT &= ~STEPPER_MASK;
        STEPPER_PORT |= newOutput;
    }
    else
    {
        STEPPER_PORT &= ~STEPPER_MASK;
    }
}
