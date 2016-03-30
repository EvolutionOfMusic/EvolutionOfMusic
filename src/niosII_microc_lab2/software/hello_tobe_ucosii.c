/*************************************************************************
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
**************************************************************************
* Description:                                                           *
* The following is a simple hello world program running MicroC/OS-II.The * 
* purpose of the design is to be a very simple application that just     *
* demonstrates MicroC/OS-II running on NIOS II.The design doesn't account*
* for issues such as checking system call return codes. etc.             *
*                                                                        *
* Requirements:                                                          *
*   -Supported Example Hardware Platforms                                *
*     Standard                                                           *
*     Full Featured                                                      *
*     Low Cost                                                           *
*   -Supported Development Boards                                        *
*     Nios II Development Board, Stratix II Edition                      *
*     Nios Development Board, Stratix Professional Edition               *
*     Nios Development Board, Stratix Edition                            *
*     Nios Development Board, Cyclone Edition                            *
*   -System Library Settings                                             *
*     RTOS Type - MicroC/OS-II                                           *
*     Periodic System Timer                                              *
*   -Know Issues                                                         *
*     If this design is run on the ISS, terminal output will take several*
*     minutes per iteration.                                             *
**************************************************************************/


#include <stdio.h>
#include "includes.h"
#include "altera_up_avalon_character_lcd.h"
#include <ucos_ii.h>

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];
OS_STK    task3_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2
#define TASK3_PRIORITY      3

/* Definition of Task Semaphores */
#define QUEUE_SIZE			8
OS_EVENT* switch_queue;
INT8U err;
void* queue_buffer[QUEUE_SIZE];



/* LCD Definitions*/
alt_up_character_lcd_dev * char_lcd_dev = (alt_up_character_lcd_dev*)CHARACTER_LCD_0_BASE;

/* Prints "Hello World"  */
void lcd_task(void* pdata)
{
  while (1)
  { 
	alt_up_character_lcd_init (char_lcd_dev);
	char message[] = "Hello World\0";

	void* switch_state=OSQPend(switch_queue,0,& err);

	if((int *) switch_state == 1){
		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 0);
		alt_up_character_lcd_string(char_lcd_dev, message);
	}
	else{
		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
		alt_up_character_lcd_string(char_lcd_dev, message);
	}
	OSTimeDlyHMSM(0,0,0,50);
  }
}
/* Prints "Hello World" and sleeps for three seconds */
void switch_task(void* pdata)
{
  while (1)
  { 
	int *on = (int*)SWITCH_BASE;
	if(*on==1){
		int state = 1;
		OSQPost(switch_queue,(void*) state);
	}
	else{
		int state = 0;
		OSQPost(switch_queue,(void*) state);
	}
	OSTimeDlyHMSM(0,0,0,50);
  }
}
/* Prints "Hello World" and sleeps for three seconds */
void led_task(void* pdata)
{
  while (1)
  {
	  int *lights = (int*)GREEN_LEDS_BASE;
	  *lights = 255;
	  OSTimeDlyHMSM(0,0,1,0);
	  *lights = 0;
	  OSTimeDlyHMSM(0,0,1,0);
  }
}
/* The main function creates two task and starts multi-tasking */
int main(void)
{
	OSInit();
	switch_queue = OSQCreate(& queue_buffer[0],QUEUE_SIZE);

	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev (CHARACTER_LCD_0_NAME);
	if( char_lcd_dev == NULL)
		alt_printf ("Error: could not open character LCD device\n");
	else
		alt_printf ("Opened character LCD device\n");

	alt_ic_isr_register(alt_u32 ic_id, alt_u32 irq, interrupt_isr_gate, NULL, NULL);

  OSTaskCreateExt(lcd_task,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(switch_task,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(led_task,
                    NULL,
                    (void *)&task3_stk[TASK_STACKSIZE-1],
                    TASK3_PRIORITY,
                    TASK3_PRIORITY,
                    task3_stk,
                    TASK_STACKSIZE,
                    NULL,
                    0);
  OSStart();
  return 0;
}

static void interrupt_isr_gate( void * context) {

	
}


/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
