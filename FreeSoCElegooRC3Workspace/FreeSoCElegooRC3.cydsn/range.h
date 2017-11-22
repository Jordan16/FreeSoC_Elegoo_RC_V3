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

#ifndef RANGE_H
#define RANGE_H
	
//include files
#include "types.h"

//defines
#define CLOCK_PERIOD_uS 0.125

//variables
volatile uint32 rangeDistance;

//function prototypes
void range_init();
void range_set_trig();
void range_capture();
int range_calc_cm();

#endif

/* [] END OF FILE */
