
#include "MKL05Z4.h" /*Device header*/
#include "keypad.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char butt[4][4] ={
	{'C','0','=','+'},
	{'1','2','3','-'},
	{'4','5','6','*'},
	{'7','8','9','/'}
};

int cLine = 0;
int rLine = 0;

void keyPadInit(){
	
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK;
	//Init keys as GPIO
	PORTA->PCR[R1] |= PORT_PCR_MUX(1);
	PORTA->PCR[R2] |= PORT_PCR_MUX(1);
	PORTA->PCR[R3] |= PORT_PCR_MUX(1);
	PORTA->PCR[R4] |= PORT_PCR_MUX(1);
	PORTA->PCR[C1] |= PORT_PCR_MUX(1);
	PORTA->PCR[C2] |= PORT_PCR_MUX(1);
	PORTA->PCR[C3] |= PORT_PCR_MUX(1);
	PORTA->PCR[C4] |= PORT_PCR_MUX(1);
	//Adding pull up resistor to keypad
	PORTA->PCR[R1] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[R2] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[R3] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[R4] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[C1] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[C2] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[C3] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[C4] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
}

void setPinsCasOutPut(){

	//Set C pins as output
	PTA->PDDR |= (1<<(C1));
	PTA->PDDR |= (1<<(C2));
	PTA->PDDR |= (1<<(C3));
	PTA->PDDR |= (1<<(C4));
	//Set R pins as input
	PTA->PDDR &= ~(1<<(R1));
	PTA->PDDR &= ~(1<<(R2));
	PTA->PDDR &= ~(1<<(R3));
	PTA->PDDR &= ~(1<<(R4));

}

void setPinsRasOutPut(){

	//Set R pins as output
	PTA->PDDR |= (1<<(R1));
	PTA->PDDR |= (1<<(R2));
	PTA->PDDR |= (1<<(R3));
	PTA->PDDR |= (1<<(R4));
	//Set C pins as input
	PTA->PDDR &= ~(1<<(C1));
	PTA->PDDR &= ~(1<<(C2));
	PTA->PDDR &= ~(1<<(C3));
	PTA->PDDR &= ~(1<<(C4));

}


int checkPinR(){
		if( ( PTA->PDIR & (1<<R1) ) ==0 )
			return 1;
		else if(( PTA->PDIR & (1<<R2) ) ==0)
			return 2;
		else if(( PTA->PDIR & (1<<R3) ) ==0)
			return 3;
		else if(( PTA->PDIR & (1<<R4) ) ==0)
			return 4;
		
		return 0;
}

int checkPinC(){
		if( ( PTA->PDIR & (1<<C1) ) ==0 )
			return 1;
		else if(( PTA->PDIR & (1<<C2) ) ==0)
			return 2;
		else if(( PTA->PDIR & (1<<C3) ) ==0)
			return 3;
		else if(( PTA->PDIR & (1<<C4) ) ==0)
			return 4;
		
		return 0;
}

char keyPressed(){
	rLine = 0;
	cLine = 0;
	setPinsCasOutPut();
	rLine = checkPinR();
	if(!rLine) return 'A'; 
	setPinsRasOutPut();
	cLine = checkPinC();
	if(!cLine) return 'A';
	return butt[rLine-1][cLine-1];
}


