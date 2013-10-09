#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "stepper.h"
#include "softUart.h"

int main(void)
{
    uint8_t tempChar;
    sei();
    stepperInit();
    stepperSetSpeed(2);
    softUartInit();
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
    return 0;
}
