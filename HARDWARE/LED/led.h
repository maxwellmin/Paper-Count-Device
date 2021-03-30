#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
/**********************************************/	 
#define KeyX_PORT GPIOF
#define KeyY_PORT GPIOF

#define KX1 GPIO_Pin_0 //P
#define KX2 GPIO_Pin_1 //P
#define KX3 GPIO_Pin_2 //P
#define KX4 GPIO_Pin_3 //P

#define KY1 GPIO_Pin_4 //P
#define KY2 GPIO_Pin_5 //P
#define KY3 GPIO_Pin_6 //P
#define KY4 GPIO_Pin_7 //P
void GPIO_Key2(void);
u8 Read_KeyValue2(void);
/**********************************************/
#define ROW1 PFin(0)// PB5
#define ROW2 PFin(1)// PB5
#define ROW3 PFin(2)// PB5
#define ROW4 PFin(3)// PB5

#define COLUMN1 PFin(4)// PE5
#define COLUMN2 PFin(5)// PE5
#define COLUMN3 PFin(6)// PE5
#define COLUMN4 PFin(7)// PE5	 

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

void LED_Init(void);//初始化

void KEY16_Init(void);//初始化
u8 KEY_Scan_Row(void);
u8 KEY_Scan_Column(void);
u8 KEY16_Scan(void);

#endif
