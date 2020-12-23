
#include "MKL05Z4.h" /*Device header*/
#include "keypad.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pit.h"


void PIT_IRQHandler(void);

char input = ' ';


void PIT_IRQHandler()
{

	input = keyPressed();
  PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}


int main()
{


	PIT_Init();
	LCD1602_Init();		 /* initialize LCD		  */
	keyPadInit();
	
	
	LCD1602_Backlight(TRUE);
	LCD1602_ClearAll();


	char y[16];

  while(1)
	{
		DELAY(5)
		sprintf(y, "%c", input);
		LCD1602_SetCursor(0,0);
		LCD1602_Print(y);
	}
}
	
	
	
	
