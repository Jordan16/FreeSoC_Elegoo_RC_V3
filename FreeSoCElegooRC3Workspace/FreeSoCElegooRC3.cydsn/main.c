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
#include "servo.h"
#include "range.h"
#include "bt.h"

//defines
#define MAX_COUNT 9

//variables
extern uint32 inter_cmd_count;
bool timer_flag = false;
uint32 period_count = 0;

//function prototypes
void appInit();

int main(void)
{
	//initialization
	appInit();

	//executive loop, program will never exit this loop
	for(;;)
	{    
		if(timer_flag)
		{
			//set range trigger
	        range_set_trig();
	        LED_Car_Shield_Write(!LED_Car_Shield_Read());
	        
	        //increment inter-command count
	        inter_cmd_count++;
	        
	        //check for bluetooth message
	        bt_check_rcv();
            
            //run the motor state machine
            motor_state_machine();
	        
	        if(period_count == 5)
	        {
	        	//blink heartbeat LED
	        	LED_freeSoC_Write(!LED_freeSoC_Read());
	        }
	        
	        //increment time counter
	        if(period_count >= MAX_COUNT)
	        {
	        	period_count = 0;
	        }
	        else
	        {
	        	period_count++;
	        }
            
            timer_flag = false;
		}
	}
}

void appInit()
{
    //start clocks
    PWM_Clock_Start();
    
    //start components
    Serial_Start();
    Timer_Start();
    
    //initialize drivers
    motor_init();
    servo_init();
    range_init();
    
    //enable interrupts
    CyGlobalIntEnable;
    isr_Timer_Start();
    
    //initialize variables
    debug = true;
    
    bt_debug_write("Init complete.");
}

/* [] END OF FILE */
