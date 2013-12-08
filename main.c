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

int main(void)
{
    //uint8_t tempChar;

    tb6560Init();
    //softUartInit();

    sei();

    while(1)
    {
        tb6560SetSpeed(250);
        tb6560SetSteps(100);
        while(tb6560GetSteps());
        tb6560SetSpeed(10);
        tb6560SetSteps(-100);
        while(tb6560GetSteps());
    }

    /*
    stepperSetSpeed(2);
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
                stepperSetSpeed(tempChar-'0');
                break;

            case 'w':
                stepperSetSteps(20);
                break;

            case 's':
                stepperSetSteps(-20);
                break;

            default:
                break;
        }
    }
    */
    return 0;
}
