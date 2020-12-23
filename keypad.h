
#ifndef keypad_h
#define keypad_h
typedef enum{ R1 = 5, R2 = 7 , R3 = 6, R4 = 8 , C1 = 9 , C2=10 , C3 = 11 , C4 = 12} ButtonType;
void keyPadInit(void);
void setPinsCasOutPut(void);
int checkPinR(void);
int checkPinC(void);
void setPinsRasOutPut(void);
char keyPressed(void);

#endif