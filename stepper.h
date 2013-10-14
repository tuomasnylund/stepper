/**
 * \file   stepper.h
 * \author Tuomas Nylund
 * \brief  Header for interrupt driven stepper controller
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

#ifndef _STEPPER_H_
#define _STEPPER_H_

#define STEPPER_PORT  PORTB /**< Port register for stepper outputs */
#define STEPPER_DDR   DDRB  /**< Data direction register for stepper outputs */
#define STEPPER_1_BIT PB2   /**<  */
#define STEPPER_2_BIT PB1   /**<  */
#define STEPPER_3_BIT PB0   /**<  */
#define STEPPER_4_BIT PB3   /**<  */
#define STEPPER_MASK  ((1<<STEPPER_1_BIT)|\
                       (1<<STEPPER_2_BIT)|\
                       (1<<STEPPER_3_BIT)|\
                       (1<<STEPPER_4_BIT))


/**
 * \brief  Initialize Stepper controller
 */
void   stepperInit(void);

/**
 * \brief  Set the speed at which the stepper steps
 *
 * \param  speed delay between steps in ~1ms steps
 */
void   stepperSetSpeed(uint8_t speed);

/**
 * \brief  Change the steps to be done
 *
 * \param  steps number of steps, positive and negative give different directions
 */
void   stepperSetSteps(int8_t steps);

/**
 * \brief  Get the steps to be done
 *
 * \return The target steps 
 */
int8_t stepperGetSteps(void);

#endif /* _STEPPER_H_ */
