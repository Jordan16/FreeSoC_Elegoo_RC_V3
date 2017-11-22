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

//include files
#include "project.h"
#include "motor.h"
#include "bt.h"

//defines
#define CMD_ARRAY_LENGTH 256

//variables
int motor_cmd_ind = 0;
int motor_cmd_array_size = 0;
motor_state motor_state_array[CMD_ARRAY_LENGTH];
uint32 motor_duration_array[CMD_ARRAY_LENGTH];

uint32 inter_cmd_count = 0;
uint32 inter_cmd_wait = 0;

bool record = false;

//function prototypes
void motor_forward();
void motor_back();
void motor_left();
void motor_right();
void motor_stop();

void motor_capture_prev();

void motor_init()
{
    mode_set(MANUAL);
    
    PWM_ENA_Start();
    PWM_ENB_Start();
    
    CyDelay(10);
    
    previous_motor_state = STOP;
    motor_send_cmd(STOP);
    
    //set globals to default values
    motor_set_record(false);
    inter_cmd_count = 0;
    inter_cmd_wait = 0;
}

void motor_state_machine()
{
    switch(current_mode)
    {
        case MANUAL:
        //don't do anything, manually controlled through bt
        break;
        
        case AUTO:
        
        break;
        
        case LINE:
        
        break;
        
        case PLAYBACK:
        if(motor_cmd_ind <= motor_cmd_array_size)
        {
            if((motor_cmd_ind == 0) || (inter_cmd_wait <= inter_cmd_count))
            {
                motor_send_cmd(motor_state_array[motor_cmd_ind]);
                if(motor_state_array[motor_cmd_ind] == STOP)
                {
                    inter_cmd_wait = 2;
                }
                else
                {
                    inter_cmd_wait = motor_duration_array[motor_cmd_ind];
                }
                motor_cmd_ind++;
            }
        }
        else
        {
            //stop after route is played back
            if(current_motor_state != STOP)
            {
                motor_send_cmd(STOP);
            }
        }
        break;
        
        default:
        break;
    }
}

void mode_set(mode new)
{
    //stop car before changing modes
    motor_stop();
    
	switch(new)
	{
		case MANUAL:
		current_mode = MANUAL;
		break;
		
		case AUTO:
		current_mode = AUTO;
		break;
        
        case LINE:
		current_mode = LINE;
		break;
		
		case PLAYBACK:
        record = false;
        motor_cmd_ind = 0;
        current_mode = PLAYBACK;
		break;
		
		default:
		break;
	}
}

void motor_send_cmd(motor_state new)
{   
    switch(new)
	{
		case FORWARD:
        motor_forward();
		break;
		
		case BACK:
		motor_back();
		break;
		
		case LEFT:
        motor_left();
		break;
		
		case RIGHT:
        motor_right();
		break;
        
        case STOP:
        motor_stop();
		break;
		
		default:
		break;
	}
}

void motor_set_record(bool enable)
{
    if(current_mode == PLAYBACK)
    {
        record = false;
        bt_debug_write("Record disabled");
    }
    else
    {
        record = enable;
        motor_cmd_ind = 0;
        if(record)
        {
            bt_debug_write("Record enabled");
        }
        else
        {
            bt_debug_write("Record disabled");
        }
    }
}

void motor_update_state(motor_state new)
{
    previous_motor_state = current_motor_state;
    current_motor_state = new;
    
    if(record)
    {
        //capture previous state and duration
        motor_state_array[motor_cmd_ind] = previous_motor_state;
        motor_duration_array[motor_cmd_ind] = inter_cmd_count;
        
        //update size and increment index
        motor_cmd_array_size = motor_cmd_ind++;
    }
    
    //reset inter_cmd_count
    inter_cmd_count = 0;
}

void motor_forward()
{
    //left motors
    PWM_ENA_WriteCompare(MAX_PWM_VAL);
    IN1_Write(1);
    IN2_Write(0);
    
    //right motors
    PWM_ENB_WriteCompare(MAX_PWM_VAL);
    IN3_Write(0);
    IN4_Write(1);
    
    motor_update_state(FORWARD);
    
    bt_debug_write("Forward");
}

void motor_back()
{
    //left motors
    PWM_ENA_WriteCompare(MAX_PWM_VAL);
    IN1_Write(0);
    IN2_Write(1);
    
    //right motors
    PWM_ENB_WriteCompare(MAX_PWM_VAL);
    IN3_Write(1);
    IN4_Write(0);
    
    motor_update_state(BACK);
    
    bt_debug_write("Back");
}

void motor_left()
{
    //left motors
    PWM_ENA_WriteCompare(TURN_PWM_VAL);
    IN1_Write(0);
    IN2_Write(1);
    
    //right motors
    PWM_ENB_WriteCompare(TURN_PWM_VAL);
    IN3_Write(0);
    IN4_Write(1);
    
    motor_update_state(LEFT);
    
    bt_debug_write("Left");
}

void motor_right()
{
    //left motors
    PWM_ENA_WriteCompare(TURN_PWM_VAL);
    IN1_Write(1);
    IN2_Write(0);
    
    //right motors
    PWM_ENB_WriteCompare(TURN_PWM_VAL);
    IN3_Write(1);
    IN4_Write(0);
    
    motor_update_state(RIGHT);
    
    bt_debug_write("Right");
}

void motor_stop()
{
    //left motors
    PWM_ENA_WriteCompare(MIN_PWM_VAL);
    //IN1_Write(1);
    //IN2_Write(0);
    
    //right motors
    PWM_ENB_WriteCompare(MIN_PWM_VAL);
    //IN3_Write(0);
    //IN4_Write(1);
    
    motor_update_state(STOP);
    
    bt_debug_write("Stop");
}

/* [] END OF FILE */
