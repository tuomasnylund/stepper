/**
 * \file   main.c
 * \author Tuomas Nylund
 * \brief  Main source file for serial controlled stepper driver
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
#include <util/delay.h>
#include <avr/interrupt.h>

#include "tb6560.h"
#include "softUart.h"

static uint8_t C_speeds[] = {15,20,25,30,40,60,100,160,240};

int main(void)
{
    uint8_t tempChar;

    tb6560Init();
    softUartInit();

    sei();

    tb6560SetSpeed(20);
    tb6560SetSteps(20);
    while(1)
    {
        while(!softUartNewChar());

        tempChar = softUartGetChar();

        switch (tempChar)
        {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                tb6560SetSpeed(C_speeds[tempChar-'0'-1]);
                break;

            case 'w':
                tb6560SetSteps(20);
                break;

            case 's':
                tb6560SetSteps(-20);
                break;

            default:
                break;
        }
    }
    return 0;
}
