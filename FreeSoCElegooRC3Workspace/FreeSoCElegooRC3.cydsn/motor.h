/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef MOTOR_H
#define MOTOR_H
	
//include files
#include "types.h"

//defines
#define MAX_PWM_VAL 255
#define MIN_PWM_VAL 0
    
#define TURN_PWM_VAL 170
    
//variables
typedef enum
{
    MANUAL,
    AUTO,
    LINE,
    PLAYBACK
} mode;
    
mode current_mode;

typedef enum
{
    STOP,
    FORWARD,
    BACK,
    LEFT,
    RIGHT
} motor_state;

motor_state previous_motor_state;
motor_state current_motor_state;

//function prototypes
void motor_init();
void motor_state_machine();
void mode_set(mode new);
void motor_send_cmd(motor_state new);
void motor_set_record(bool enable);

#endif

/* [] END OF FILE */
