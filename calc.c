
#include "MKL05Z4.h" /*Device header*/
#include "keypad.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"

int64_t CalcResult(int64_t r1, int64_t r2, char operation){

	switch(operation){
		case '=':
			break;
		case '-':
			r1 = r1-r2;
			break;
		case '*':
			r1 = r1*r2;
			break;
		case '+':
			r1 = r1+r2;
			break;
		default:
			break;
	}
	
	return r1;


}