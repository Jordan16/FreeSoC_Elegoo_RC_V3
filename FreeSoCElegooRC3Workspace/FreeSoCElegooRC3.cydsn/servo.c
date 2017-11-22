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

//Total PWM period is 20ms
//one clock = 0.01ms

//servo angle is determined by high pulse length
//0.5ms =   0 degrees
//1.0ms =  45 degrees
//1.5ms =  90 degrees
//2.0ms = 135 degrees
//2.5ms = 180 degrees

//include files
#include "project.h"
#include "servo.h"

//defines
#define SERVO_ZERO_OFFSET 50
#define SERVO_MIN_COMP    72 //about 20 deg
#define SERVO_MAX_COMP    228 //about 160 deg

void servo_init()
{
    PWM_Servo_Start();
    
    CyDelay(10);
    
    servo_set_angle(90);
}

void servo_set_angle(uint8 angle)
{
    uint16 comp_val;
    
    //calculate comp val
    comp_val = SERVO_ZERO_OFFSET + ((angle * 50)/45);
    
    //check limits
    if(comp_val < SERVO_MIN_COMP)
    {
        comp_val = SERVO_MIN_COMP;
    }
    else if(comp_val > SERVO_MAX_COMP)
    {
        comp_val = SERVO_MAX_COMP;
    }
   
    //program comp value
    PWM_Servo_WriteCompare((uint16)comp_val);
}

/* [] END OF FILE */
