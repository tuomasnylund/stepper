#ifndef _STEPPER_H_
#define _STEPPER_H_

#define STEPPER_PORT  PORTB
#define STEPPER_DDR   DDRB
#define STEPPER_1_BIT PB2
#define STEPPER_2_BIT PB1
#define STEPPER_3_BIT PB0
#define STEPPER_4_BIT PB3
#define STEPPER_MASK  ((1<<STEPPER_1_BIT)|\
                       (1<<STEPPER_2_BIT)|\
                       (1<<STEPPER_3_BIT)|\
                       (1<<STEPPER_4_BIT))


void   stepperInit(void);
void   stepperSetSpeed(uint8_t speed);
void   stepperSetSteps(int8_t steps);
int8_t stepperGetSteps(void);

 

#endif /* _STEPPER_H_ */
