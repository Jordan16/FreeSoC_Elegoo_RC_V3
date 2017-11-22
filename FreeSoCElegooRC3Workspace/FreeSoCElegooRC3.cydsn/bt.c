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
#include "bt.h"
#include "motor.h"

void bt_init()
{
	//set flags
	debug = false;
}

void bt_debug_write(const char8 string[])
{
	Serial_PutString(string);
	
	Serial_PutString("\r\n");
}

bool bt_check_rcv()
{
    bool bt_rcvd = false;
    char readVal;
    
    if(Serial_GetRxBufferSize() >= 1)
    {
        readVal = Serial_GetChar();   
	
	    switch(readVal)
	    {
            //modes
            case 'm': //MANUAL
            mode_set(MANUAL);
            break;
            
            case 'a': //AUTO
            mode_set(AUTO);
            break;
            
            case 'i': //LINE
            mode_set(LINE);
            break;
            
            case 'p': //PLAYBACK
            mode_set(PLAYBACK);
            break;          
            
            //motor states
	   	    case 'f':
            motor_send_cmd(FORWARD);
	   	    break;
	   	    
	   	    case 'b':
	   	    motor_send_cmd(BACK);
	   	    break;
	   	    
	        case 'l':
	   	    motor_send_cmd(LEFT);
	   	    break;
	   	    
	   	    case 'r':
	   	    motor_send_cmd(RIGHT);
	   	    break;
	   	    
	   	    case 's':
	   	    motor_send_cmd(STOP);
	   	    break;
            
            //other
            case 'e': //RECORD
            motor_set_record(true);
            break;
            
            case 'd': //Debug
            debug = ! debug;
            
            if(debug)
            {
                bt_debug_write("Debug enabled");
            }
		
		    default:
		    break;
        }
        
        bt_rcvd = true;
	}
    
    return bt_rcvd;
}

/* [] END OF FILE */
