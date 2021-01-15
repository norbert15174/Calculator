
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
unsigned int i = 0;
int changeValue = 0;
double currentValue = 0;
double savedValue = 0;
char result[16];
int clear = 0;
char display[20] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
char operation = 'A';
void clearTheValue(void);
void setNumber(void);
void displayResultHandler(void);
char operationValue[2];
char lastOperation = 'A';
int equal = 0;

void setNumber()
{
        if (clear)
        {
                LCD1602_ClearAll();
                clear = 0;
                LCD1602_SetCursor(0, 1);
                if (operation != 'A')
                {
                        sprintf(operationValue, "%c", operation);
                        LCD1602_Print(operationValue);
                }
        }
        result[i] = input;
        currentValue = atof(result);
        if (currentValue >= 0 && currentValue == (int64_t)currentValue)
                sprintf(display, "%llu", (int64_t)currentValue);
        else
                sprintf(display, "%f", currentValue);
}

void clearTheValue()
{

        operation = 'A';
        currentValue = 0;
        savedValue = 0;
        equal = 0;
        i = 0;
        LCD1602_ClearAll();
        sprintf(result, "%s", "                ");
        sprintf(display, "%llu", (int64_t)currentValue);
}

void PIT_IRQHandler()
{

        if (!changeValue)
                changeValue = 1;

        PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}

char checkTheValue(char oper)
{

        if (operation == 'A')
        {
                savedValue = currentValue;
                sprintf(display, "%c", '0');
                i = 0;
                LCD1602_ClearAll();
                sprintf(result, "%s", "                ");
        }
        else
        {
                clear = 1;
                i = 0;
                LCD1602_ClearAll();
                currentValue = CalcResult(savedValue, currentValue, operation);
                savedValue = currentValue;
                equal = 0;
                sprintf(result, "%s", "                ");
                if (currentValue == (int64_t)currentValue)
                        sprintf(display, "%lld", (int64_t)currentValue);
                else
                        sprintf(display, "%f", currentValue);
        }
        LCD1602_SetCursor(0, 1);
        sprintf(operationValue, "%c", oper);
        LCD1602_Print(operationValue);
        return oper;
}

void displayResultHandler()
{

        switch (input)
        {
        case '=':
                if (operation == 'A')
                {
                        i--;
                        currentValue = atof(result);
                        sprintf(display, "%lld", (int64_t)currentValue);
                }
                else
                {

                        LCD1602_ClearAll();
                        currentValue = CalcResult(savedValue, currentValue, operation);
                        savedValue = 0;
                        sprintf(result, "%s", "                ");
                        if (currentValue == (int64_t)currentValue)
                                sprintf(display, "%lld", (int64_t)currentValue);
                        else
                                sprintf(display, "%f", currentValue);
                        LCD1602_SetCursor(0, 1);
                        sprintf(operationValue, "%c", ' ');
                        LCD1602_Print(operationValue);
                        equal = 1;
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
                if (equal == 1)
                {
                }
                else
                {
                        setNumber();
                        break;
                }
        }
}

int main()
{

        PIT_Init();
        LCD1602_Init(); /* initialize LCD		  */
        keyPadInit();
        LCD1602_Backlight(TRUE);
        LCD1602_ClearAll();
        LCD1602_SetCursor(0, 0);
        sprintf(display, "0");
        LCD1602_SetCursor(0, 0);
        LCD1602_Print(display);

        while (1)
        {

                if (changeValue)
                {
                        input = keyPressed();
                        if (lastOperation != input)
                        {
                                lastOperation = input;
                                if (input != 'A' && i < 12)
                                {
                                        displayResultHandler();
                                        LCD1602_SetCursor(0, 0);
                                        LCD1602_Print(display);
                                        changeValue = 0;
                                        i++;
                                }
                                else if (i >= 12)
                                {

                                        i = 11;
                                }
                        }
                }
        }
}
