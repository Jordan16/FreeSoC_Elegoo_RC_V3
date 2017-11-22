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

#ifndef BT_H
#define	BT_H

//include files
//#include <stdbool.h>
#include "types.h"

//global variables
bool debug; //enables or disables debug messages over the Debug UART

//function prototypes
void bt_init();
void bt_debug_write(const char8[]);
bool bt_check_rcv();

#endif

//[] END OF FILE
