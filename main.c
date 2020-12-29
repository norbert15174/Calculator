
#include "MKL05Z4.h" /*Device header*/
#include "keypad.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pit.h"
#include "calc.h"


void PIT_IRQHandler(void);

char input = ' ';
int i = -1;
int changeValue = 0;
double currentValue = 0;
double savedValue = 20;
char result[16];

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
	char operation = 'A';

	LCD1602_SetCursor(0,0);
	sprintf(display,"0");
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);

  while(1)
	{
		
		if(changeValue){
			switch(input){
				case '=':
					if(operation == 'A'){
						operation = input;
						savedValue = currentValue;
						sprintf(display,"%c",input);
						LCD1602_ClearAll();
						i=0;
						sprintf(result,"%s","                ");
					}
					break;
				case '+':
					if(operation == 'A'){
					savedValue = currentValue;
					operation = '+';
					sprintf(display,"%c",input);
					i=0;
					LCD1602_ClearAll();
					sprintf(result,"%s","                ");
					}else{
						LCD1602_ClearAll();
						sprintf(display,"%f",CalcResult(savedValue,currentValue,operation));
					}
					break;
				case '-':
					sprintf(display,"%c",input);
					i=0;
					LCD1602_ClearAll();
					sprintf(result,"%s","                ");
					break;
				case '/':
					sprintf(display,"%c",input);
					i=0;
					LCD1602_ClearAll();
					sprintf(result,"%s","                ");
					break;
				case 'C':
					sprintf(display,"%c",input);
					i=0;
					LCD1602_ClearAll();
					sprintf(result,"%s","                ");
					break;
				default:
					result[i] = input;
					currentValue = atof(result);
					if(currentValue == (int64_t)currentValue)
						sprintf(display,"%llu",(int64_t)currentValue);
					else
						sprintf(display,"%f",currentValue);

				break;
			}
			changeValue = 0;
			LCD1602_SetCursor(0,0);
			LCD1602_Print(display);
		}
					
	}
}


	
	
	
