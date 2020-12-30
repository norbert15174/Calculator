
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
char checkTheValue(char oper);
char input = ' ';
int i = -1;
int changeValue = 0;
double currentValue = 0;
double savedValue = 0;
char result[16];
int clear = 0;
char display[20] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
char operation = 'A';
void clearTheValue(void);
void setNumber(void);
void displayResultHandler(void);
char operationValue[2];
	
void setNumber(){
	if(clear){
						LCD1602_ClearAll();
						clear=0;
						LCD1602_SetCursor(0,1);
		if(operation != 'A'){
			sprintf(operationValue,"%c",operation);
						LCD1602_Print(operationValue);
		}
						
					} 
					result[i] = input;
					currentValue = atof(result);
					if( currentValue >= 0 && currentValue == (int64_t)currentValue )
						sprintf(display,"%llu",(int64_t)currentValue);
					else
						sprintf(display,"%f",currentValue);

}

void clearTheValue(){

		operation = 'A';
		currentValue = 0;
		savedValue = 0;
		i=0;
		LCD1602_ClearAll();
		sprintf(result,"%s","                ");
		sprintf(display,"%llu",(int64_t)currentValue);

}

void PIT_IRQHandler()
{

	input = keyPressed();
	if(input != 'A' && i<14){
		changeValue = 1;
		i++;
	}

  PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}
	
char checkTheValue(char oper){

	if(operation == 'A'){
						savedValue = currentValue;
						sprintf(display,"%c",'0');
						i=0;
						LCD1602_ClearAll();
						sprintf(result,"%s","                ");
					}else{
						clear=1;
						LCD1602_ClearAll();
						currentValue = CalcResult(savedValue,currentValue,operation);
						savedValue = currentValue;
						sprintf(result,"%s","                ");
					if(currentValue >= 0 && currentValue == (int64_t)currentValue)
						sprintf(display,"%llu",(int64_t)currentValue);
					else
						sprintf(display,"%f",currentValue);
					}
						LCD1602_SetCursor(0,1);
						sprintf(operationValue,"%c",oper);
						LCD1602_Print(operationValue);
	return oper;

}

void displayResultHandler(){

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
					operation = checkTheValue('+');
					break;
				case '-':
					operation = checkTheValue('-');
					break;
				case '*':
					operation = checkTheValue('*');
					break;
				case '/':
					operation = checkTheValue('/');
					break;
				case 'C':
					clearTheValue();
					break;
				default:
					setNumber();
				break;
}}


int main()
{


	PIT_Init();
	LCD1602_Init();		 /* initialize LCD		  */
	keyPadInit();
	LCD1602_Backlight(TRUE);
	LCD1602_ClearAll();
	LCD1602_SetCursor(0,0);
	sprintf(display,"0");
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);

  while(1)
	{
		
		if(changeValue){
				displayResultHandler();
		}
		
		changeValue = 0;
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		
		}
	}



	
	
	
