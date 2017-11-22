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
#include "range.h"
#include "motor.h"
#include "bt.h"

//variables


void range_init()
{
    Counter_Range_Start();
    
    isr_Range_Start();
    
    Control_Reg_Trigger_Write(0);
}

void range_set_trig()
{
    //set the trigger
    Control_Reg_Trigger_Write(1);
    
    CyDelayUs(10);
    
    Control_Reg_Trigger_Write(0);
}

void range_capture()
{
    uint8 status = 0;
    uint32 clkCounts = 0, pulseLength = 0;
    
    status = Counter_Range_ReadStatusRegister();
    
    if(status & Counter_Range_STATUS_CAPTURE)
    {
        while(status & Counter_Range_STATUS_FIFONEMP)
        {
            clkCounts = Counter_Range_ReadCapture();
            status = Counter_Range_ReadStatusRegister();
        }
        
        //calculate range
        pulseLength = clkCounts * CLOCK_PERIOD_uS;
        
        //formula comes from instructables example code
        //http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/
        rangeDistance = (pulseLength/2) / 29.1;
        
        if((current_motor_state == FORWARD) && (rangeDistance <= 20))
        {
            motor_send_cmd(STOP);
            bt_debug_write("Range tripped");
        }
    }
}

/* [] END OF FILE */
