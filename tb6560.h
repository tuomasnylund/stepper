/**
 * \file   tb6560.h
 * \author Tuomas Nylund
 * \brief  Header file for TB6560 stepper driver controller
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

#ifndef TB6560
#define TB6560

#define TB6560_EN_PORT  PORTB
#define TB6560_EN_DDR   DDRB
#define TB6560_EN_BIT   PB3

/* OC1B */
#define TB6560_CLK_PORT PORTB
#define TB6560_CLK_DDR  DDRB
#define TB6560_CLK_BIT  PB4

#define TB6560_DIR_PORT PORTB
#define TB6560_DIR_DDR  DDRB
#define TB6560_DIR_BIT  PB1

#define PRESCALER_CLEAR_MASK (~((uint8_t)0b1111))
#define PRESCALER_VALUE      8

/**
 * \brief  Initialize Stepper controller
 */
void   tb6560Init(void);

/**
 * \brief  Set the speed at which the stepper steps
 *
 * \param  speed delay between steps in ~1ms steps
 */
void   tb6560SetSpeed(uint8_t speed);

/**
 * \brief  Change the steps to be done
 *
 * \param  steps number of steps, positive and negative give different directions
 */
void   tb6560SetSteps(int16_t steps);

/**
 * \brief  Get the steps to be done
 *
 * \return The target steps 
 */
int16_t tb6560GetSteps(void);



#endif /* TB6560 */
