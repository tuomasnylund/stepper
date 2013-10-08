#include <avr/io.h>
#include "stepper.h"

static uint8_t C_stepperMasks[] = 
{
    1<<STEPPER_1_BIT, 1<<STEPPER_2_BIT, 1<<STEPPER_3_BIT, 1<<STEPPER_4_BIT
};

static uint8_t stepperNextState(uint8_t *state, int8_t direction)
{
    if ( direction > 0 )
        *state += 1;
    else if ( direction < 0 )
        *state -= 1;

    *state %= 4;

    return *state;
}

void stepperInit(void)
{
    STEPPER_DDR  |= STEPPER_MASK;
}

void stepperStep(int8_t amount)
{
    static uint8_t state = 0;

    STEPPER_PORT &= ~STEPPER_MASK;
    STEPPER_PORT |= C_stepperMasks[ state ];
    STEPPER_PORT |= C_stepperMasks[ stepperNextState( &state, amount ) ];
}
