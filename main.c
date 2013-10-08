#include <avr/io.h>
#include <util/delay.h>

#include "stepper.h"

int main(void)
{
    stepperInit();
    while(1)
    {
        _delay_ms(2);
        stepperStep(-1);
    }
    return 0;
}
