#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "stepper.h"

int main(void)
{
    sei();
    stepperInit();
    stepperSetSpeed(2);
    while(1)
    {
        stepperSetSteps(-20);
        while(stepperGetSteps());
        stepperSetSteps(100);
        while(stepperGetSteps());
        _delay_ms(1000);
    }
    return 0;
}
