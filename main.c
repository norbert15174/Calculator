
#include "MKL05Z4.h" /*Device header*/
#include "keypad.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>






void delay_ms( int n) {
volatile int i;
volatile int j;
for( i = 0 ; i < n; i++)
for(j = 0; j < 3500; j++) {}
}


int main()
{
	char xd[1];
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	

	LCD1602_Init();		 /* initialize LCD		  */
	LCD1602_Backlight(TRUE);

	LCD1602_SetCursor(0,0);



	keyPadInit();
	
	
  while(1)
	{
		delay_ms(10);
		xd[0] = keyPressed();
		LCD1602_SetCursor(0,0);
		LCD1602_Print(xd);
	
	}
}
	
	
	
	
