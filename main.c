
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
int i = -1;
int changeValue = 0;
int64_t currentValue = 0;
int64_t savedValue = 0;

void PIT_IRQHandler()
{

	input = keyPressed();
	if(input != 'A' && i<14){
		changeValue = 1;
		i++;
	}

  PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}


int main()
{


	PIT_Init();
	LCD1602_Init();		 /* initialize LCD		  */
	keyPadInit();
	
	
	LCD1602_Backlight(TRUE);
	LCD1602_ClearAll();


	char display[20] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	char result[16];
	char operation;

	LCD1602_SetCursor(0,0);
	sprintf(display,"0");
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);

  while(1)
	{
		
		if(changeValue){
			switch(input){
				case '=':
					changeValue = 0;
				sprintf(display,"%c",input);
				LCD1602_ClearAll();
				i=0;
					break;
				case '+':
					changeValue = 0;
				sprintf(display,"%c",input);
				i=0;
				LCD1602_ClearAll();
					break;
				case '-':
					changeValue = 0;
				sprintf(display,"%c",input);
				i=0;
				LCD1602_ClearAll();
					break;
				case '/':
					changeValue = 0;
				sprintf(display,"%c",input);
				i=0;
				LCD1602_ClearAll();
					break;
				case 'C':
					changeValue = 0;
				sprintf(display,"%c",input);
				i=0;
				LCD1602_ClearAll();
					break;
				default:
					result[i] = input;
					changeValue = 0;
					currentValue = atoll(result);
					sprintf(display,"%llu",currentValue);

				break;
			}
		}
					LCD1602_SetCursor(0,0);
					LCD1602_Print(display);
	}
}
	
	
	
	
