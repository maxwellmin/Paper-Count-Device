#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "usmart.h" 
#include "ssy.h"
#include "fdc2214.h"
#include "timer.h"
#include "beep.h"

void Sys_Init(void);
u8 pan_jue(void);
u8 pan_jue2(void);
u8 pan_jue3(void);
u8 pan_jue4(void);
u8 pan_jue5(void);
void xun_lian(u8 j);
void xian_shi(u8 result);
//void xian_shi2(u8 result);
//void xian_shi3(u8 result);
//void xian_shi4(u8 result);
u8 key,keyval,number=0,flag=0,flag1=0;
u8 gongzuo,gongzuo2,xuexi,youxi,result,dazhao;
u8 fahui1,fahui2,fahui3;
u8 zengjia,jianshao;

float res1,res2;//�ж϶�ȡֵ
float temp1,temp2,X1,X2;//��ʼֵ
float re1,re2;
float data1[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//�о�ֵ
float data2[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float info1[100];
float info2[100];
int dire1[100];
int dire2[100];
int main(void)
{
	Sys_Init();//������ʼ��	
	///////////////////��������//////////////
//	X1=res1-res3;//��������ĳ�ʼ��ֵ
//	X2=res2-res0;//���������ʼ��ֵ
///////////////////////���ֹ���//////////////////////////////////////////////////
	 while(font_init()) 		//����ֿ�
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}
/////////////////////////���ֹ�����ϣ�������/////////////////////////////////����16*16/12*12/24*24	 
  POINT_COLOR=RED;       
	Show_Str(6,6,224,16,"2019TI����ѧ��������ƾ���",16,0);
	Show_Str(6,22,144,16,"F�⣺ֽ�ż�����ʾװ��",16,0);
	Show_Str(6,38,48,16,"����:",16,0);
	Show_Str(6,54,80,16,"����ģʽ:",16,0);
	Show_Str(6,70,80,16,"ѵ������:",16,0);
	Show_Str(6,86,48,16,"��ǰ:",16,0);
	Show_Str(6,102,96,16,"CH1:00000.00",16,0);
	Show_Str(6,118,96,16,"��1:00000.00",16,0);
	Show_Str(6,134,96,16,"CH2:00000.00",16,0);
	Show_Str(6,150,96,16,"��2:00000.00",16,0);
	Show_Str(6,198,96,48,"ֽ����:",48,0);
	POINT_COLOR=BLUE;
	while(1)
	{				
		
		key=KEY16_Scan();//			key=Read_KeyValue2();
		if(key) 
		{
			keyval=key;
			LCD_ShowxNum(54,38,keyval,2,16,0);
			switch(key)
			{
				case 1: Show_Str(86,54,96,16,"ѵ�� ",16,0);gongzuo=0;gongzuo2=0;fahui1=0;flag1=0;zengjia=0;jianshao=0;BEEP=0;break;
				case 2: Show_Str(86,54,96,16,"����",16,0);
								gongzuo=1;gongzuo2=0;fahui1=0;flag1=0;zengjia=0;jianshao=0;dazhao=1;
								BEEP=1;
								delay_ms(1000);//��ʱ500ms
								BEEP=0;		
								break;
				case 3: Show_Str(86,70,96,16,"��1 ",16,0);zengjia=1;gongzuo=0;gongzuo2=0;fahui1=0;flag1=0;BEEP=0;break;
				case 4: Show_Str(86,70,96,16,"��1 ",16,0);jianshao=1;gongzuo=0;gongzuo2=0;fahui1=0;flag1=0;BEEP=0;break;
				case 5: Show_Str(86,54,96,16,"ѧϰ",16,0);gongzuo=0;gongzuo2=0;fahui1=0;xuexi=1;zengjia=0;jianshao=0;BEEP=0;break;
				case 9: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"2��ֽ",16,0);number=2;flag=1;BEEP=0;break;
				case 13:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"3��ֽ",16,0);number=3;flag=1;BEEP=0;break;
				case 6: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"4��ֽ",16,0);number=4;flag=1;BEEP=0;break;
				case 7: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"5��ֽ",16,0);number=5;flag=1;BEEP=0;break;
				case 8: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"6��ֽ",16,0);number=6;flag=1;BEEP=0;break;
				case 10:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"7��ֽ",16,0);number=7;flag=1;BEEP=0;break;
				case 11:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"8��ֽ",16,0);number=8;flag=1;BEEP=0;break;
				case 12:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"9��ֽ",16,0);number=9;flag=1;BEEP=0;break;
				case 14:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"10��ֽ",16,0);number=10;flag=1;BEEP=0;break;
				case 15:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"��λ",16,0);number=12;flag=1;BEEP=0;break;
				case 16:Show_Str(86,54,96,16,"����",16,0);gongzuo=0;gongzuo2=0;fahui1=1;flag1=1;fahui3=1;break;
				default:flag=0;break;
			}
		}
		
		LCD_ShowxNum(38,102,res1*500,5,16,0);re1=res1;LCD_ShowxNum(86,102,(res1-re1)*100,2,16,0);
		LCD_ShowxNum(38,118,temp1*500,5,16,0);re1=res1;LCD_ShowxNum(86,118,(res1-re1)*100,2,16,0);
		LCD_ShowxNum(38,134,res2*500,5,16,0);re2=res2;LCD_ShowxNum(86,134,(res2-re2)*100,2,16,0);
		LCD_ShowxNum(38,150,temp2*500,5,16,0);re2=res2;LCD_ShowxNum(86,150,(res2-re2)*100,2,16,0);
//		LCD_ShowxNum(38,246,temp0*100,5,16,0);LCD_ShowxNum(38,262,temp1*100,5,16,0);
//		LCD_ShowxNum(38,278,temp2*100,5,16,0);LCD_ShowxNum(38,294,temp3*100,5,16,0);	
		
		if(gongzuo)//����--------------------------------
		{
			if((res1*500-temp1*500)>1000&&(res2*500-temp2*500)>1000)
			{
				result=99;xian_shi(result);
			}
			else
			{
			 result=pan_jue();xian_shi(result); 
			}
		}
		else
		{		if(!fahui1)//ѵ��-----------------------------
				{
					if(zengjia)
					{
						zengjia=0;
						number++;
						LCD_Fill(54,86,86,102,WHITE);LCD_ShowxNum(54,86,number,2,16,0);Show_Str(102,86,48,16,"OK!   ",16,0);
					}
					else if(jianshao)
					{
						jianshao=0;
						number--;
						LCD_Fill(54,86,86,102,WHITE);LCD_ShowxNum(54,86,number,2,16,0);Show_Str(102,86,48,16,"OK!   ",16,0);
					}
					else if(xuexi)
					{
						xuexi=0;
						xun_lian(number);Show_Str(102,86,48,16,"go!",16,0);
					}
					else LCD_Fill(102,86,126,102,WHITE);																
					
//					if(flag) { flag=0;Show_Str(102,86,48,16,"OK!",16,0);xun_lian(number); }
	//				else LCD_Fill(102,86,126,102,WHITE);
				}
				
/*				else//����1----------------------------------
				{ if(!fahui3)
					{
						if(flag1)
						{
							//����1
							if(res1-(res3+X1)>1.5)
							{//��������
								result = 1;
								delay_ms(1000);delay_ms(1000);
							}
							else if((res3+X1)-res1>1.5)//��������
								{
									result=2;delay_ms(1000);delay_ms(1000);
								}
								else if(res2-(res0+X2)>1.5)//��������
									{
										result=3;
										delay_ms(1000);delay_ms(1000);
									}else if((res0+X2)-res2>1.5)//��������
									{
										result=4;
										delay_ms(1000);delay_ms(1000);
									}
									xian_shi3(result);
									delay_ms(500);delay_ms(500);
									delay_ms(500);delay_ms(500);
						}
					}
					else//����3----------------------------------
					{ result=pan_jue5();xian_shi4(result); }
					
				}//����12
*/
			}//ѵ��
		}//�о�1��2
		
	}


void Sys_Init(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	usmart_dev.init(72);		//��ʼ��USMART		
// 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	BEEP_Init();         	//��ʼ���������˿�
	W25QXX_Init();				//��ʼ��W25Q128
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH.
	
	KEY16_Init();
	while(FDC2214_Init())
		LCD_ShowString(30,50,200,16,16,"FDC2214 Error!");
	LCD_Fill(30,50,142,66,WHITE);
	
	delay_ms(100);
	temp1 = Cap_Calculate(0);//��ȡ��ʼֵ
//	temp1 = Cap_Calculate(1);
	temp2 = Cap_Calculate(2);
//	temp3 = Cap_Calculate(3);
	TIM5_Ctrl_Init(2000-1,720-1);
}

//��ʱ��5�жϷ������
void TIM5_IRQHandler(void)   //TIM5�ж�
{
	if(TIM5->SR&0X0001)//20ms��ʱ�ж�
 {
	res1 = Cap_Calculate(0);//�ɼ�����
//	res1 = Cap_Calculate(1);
	res2 = Cap_Calculate(2);
//	res3 = Cap_Calculate(3);
//	Data_Send_Status(res,0,0);
//	printf("%5d : %5d : %5d\r\n",res0,res1,res2);
//	 led=~led;
 }
 TIM5->SR&=~(1<<0);  //�жϱ�־λ��0���ȴ���һ���ж�
}
//********************�о�***************************//
//float wucha0=0.5,wucha1=0.5,wucha2=0.5,wucha3=0.5;
float wucha0=150,wucha1=50,wucha2=150 ,wucha3=50;                         
float wuch0=70,wuch1=25,wuch2=70,wuch3=25;
float wuc0=30,wuc1=25,wuc2=30,wuc3=25;
float wu0=20,wu1=25,wu2=20,wu3=25;
float w0=16,w1=25,w2=16,w3=25;
u8 pan_jue(void)
{
		u8 i,j;
	for(i=0;i<100;i++)
	{
		if(i<=15)
		{ 
		  if(myabsf(res1*500-info1[i])<=wucha0&&myabsf(res2*500-info2[i])<=wucha2)
			{
		    j=i+1;break;
		  }
			else j=0;
		}
		else if(15<i<=27)
		{
			if(myabsf(res1*500-info1[i])<=wuch0&&myabsf(res2*500-info2[i])<=wuch2)
			{
				j=i+1;break;
			}
			else j=0;
	  }
		else if(28<=i<=35)
		{
			if(myabsf(res1*500-info1[i])<=wu0&&myabsf(res2*500-info2[i])<=wu2)
			{
				j=i+1;break;
			}
			else j=0;
	  }
		else if(i>35)
		{
			if(myabsf(res1*500-info1[i])<=w0&&myabsf(res2*500-info2[i])<=w2)
			{
				j=i+1;break;
			}
			else j=0;
	  }
	}
	return j;
}

//********************ѵ��***************************//
void xun_lian(u8 j)
{
//	u8 i;
//	for(i=0;i<8;i++)
//	{
//		if(myabsf(res0-data0[i])<0.5)
//			return i+1;
//		else
//			return 0;
//	}
	delay_ms(100);
	info1[j-1]=res1*500;
//	info1[j-1]=res1*500;
	info2[j-1]=res2*500;
//	info3[j-1]=res3*500;
}

//********************��ʾ***************************//
void xian_shi(u8 result)
{
	switch(result)
	{
		case 0:Show_Str(54,198,96,24,"�����",24,0);break;
		case 1:Show_Str(54,198,96,24,"  1��    ",24,0);break;
		case 2:Show_Str(54,198,96,24,"  2��    ",24,0);break;
		case 3:Show_Str(54,198,96,24,"  3��    ",24,0);break;
		case 4:Show_Str(54,198,96,24,"  4��    ",24,0);break;
		case 5:Show_Str(54,198,96,24,"  5��    ",24,0);break;
		case 6:Show_Str(54,198,96,24,"  6��    ",24,0);break;
		case 7:Show_Str(54,198,96,24,"  7��    ",24,0);break;
		case 8:Show_Str(54,198,96,24,"  8��    ",24,0);break;
		case 9:Show_Str(54,198,96,24,"  9��    ",24,0);break;
		case 10:Show_Str(54,198,96,24,"  10��   ",24,0);break;
		case 11:Show_Str(54,198,96,24,"  11��   ",24,0);break;
		case 12:Show_Str(54,198,96,24,"  12��   ",24,0);break;
		case 13:Show_Str(54,198,96,24,"  13��   ",24,0);break;
		case 14:Show_Str(54,198,96,24,"  14��   ",24,0);break;
		case 15:Show_Str(54,198,96,24,"  15��   ",24,0);break;
		case 16:Show_Str(54,198,96,24,"  16��   ",24,0);break;
		case 17:Show_Str(54,198,96,24,"  17��   ",24,0);break;
		case 18:Show_Str(54,198,96,24,"  18��   ",24,0);break;
		case 19:Show_Str(54,198,96,24,"  19��   ",24,0);break;
		case 20:Show_Str(54,198,96,24,"  20��   ",24,0);break;
		case 21:Show_Str(54,198,96,24,"  21��   ",24,0);break;
		case 22:Show_Str(54,198,96,24,"  22��   ",24,0);break;
		case 23:Show_Str(54,198,96,24,"  23��   ",24,0);break;
		case 24:Show_Str(54,198,96,24,"  24��   ",24,0);break;
		case 25:Show_Str(54,198,96,24,"  25��   ",24,0);break;
		case 26:Show_Str(54,198,96,24,"  26��   ",24,0);break;
		case 27:Show_Str(54,198,96,24,"  27��   ",24,0);break;
		case 28:Show_Str(54,198,96,24,"  28��   ",24,0);break;
		case 29:Show_Str(54,198,96,24,"  29��   ",24,0);break;
		case 30:Show_Str(54,198,96,24,"  30��   ",24,0);break;
		case 31:Show_Str(54,198,96,24,"  31��   ",24,0);break;
		case 32:Show_Str(54,198,96,24,"  32��   ",24,0);break;
		case 33:Show_Str(54,198,96,24,"  33��   ",24,0);break;
		case 34:Show_Str(54,198,96,24,"  34��   ",24,0);break;
		case 35:Show_Str(54,198,96,24,"  35��   ",24,0);break;
		case 36:Show_Str(54,198,96,24,"  36��   ",24,0);break;
		case 37:Show_Str(54,198,96,24,"  37��   ",24,0);break;
		case 38:Show_Str(54,198,96,24,"  38��   ",24,0);break;
		case 39:Show_Str(54,198,96,24,"  39��   ",24,0);break;
		case 40:Show_Str(54,198,96,24,"  40��   ",24,0);break;
		case 41:Show_Str(54,198,96,24,"  41��   ",24,0);break;
		case 42:Show_Str(54,198,96,24,"  42��   ",24,0);break;
		case 43:Show_Str(54,198,96,24,"  43��   ",24,0);break;
		case 44:Show_Str(54,198,96,24,"  44��   ",24,0);break;
		case 45:Show_Str(54,198,96,24,"  45��   ",24,0);break;
		case 46:Show_Str(54,198,96,24,"  46��   ",24,0);break;
		case 47:Show_Str(54,198,96,24,"  47��   ",24,0);break;
		case 48:Show_Str(54,198,96,24,"  48��   ",24,0);break;
		case 49:Show_Str(54,198,96,24,"  49��   ",24,0);break;
		case 50:Show_Str(54,198,96,24,"  50��   ",24,0);break;
		case 51:Show_Str(54,198,96,24,"  51��   ",24,0);break;
		case 52:Show_Str(54,198,96,24,"  52��   ",24,0);break;
		case 53:Show_Str(54,198,96,24,"  53��   ",24,0);break;
		case 54:Show_Str(54,198,96,24,"  54��   ",24,0);break;
	  case 55:Show_Str(54,198,96,24,"  55��   ",24,0);break;
		case 56:Show_Str(54,198,96,24,"  56��   ",24,0);break;
		case 57:Show_Str(54,198,96,24,"  57��   ",24,0);break;
		case 58:Show_Str(54,198,96,24,"  58��   ",24,0);break;
		case 59:Show_Str(54,198,96,24,"  59��   ",24,0);break;
		case 60:Show_Str(54,198,96,24,"  60��   ",24,0);break;
		case 61:Show_Str(54,198,96,24,"  61��   ",24,0);break;
		case 62:Show_Str(54,198,96,24,"  62��   ",24,0);break;
		case 63:Show_Str(54,198,96,24,"  63��   ",24,0);break;
		case 64:Show_Str(54,198,96,24,"  64��   ",24,0);break;
		case 65:Show_Str(54,198,96,24,"  65��   ",24,0);break;
		case 66:Show_Str(54,198,96,24,"  66��   ",24,0);break;
		case 67:Show_Str(54,198,96,24,"  67��   ",24,0);break;
		case 68:Show_Str(54,198,96,24,"  68��   ",24,0);break;
		case 69:Show_Str(54,198,96,24,"  69��   ",24,0);break;
		case 70:Show_Str(54,198,96,24,"  70��   ",24,0);break;
		case 99:Show_Str(54,198,96,24,"�����·",24,0);break;	
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}

/*
void xian_shi2(u8 result)
{
	switch(result)
	{
		case 4:LCD_ShowxNum(54,198,1,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 5:LCD_ShowxNum(54,198,2,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 6:LCD_ShowxNum(54,198,3,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 7:LCD_ShowxNum(54,198,4,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 8:LCD_ShowxNum(54,198,5,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}
void xian_shi3(u8 result)
{
	switch(result)
	{
		case 1:Show_Str(54,198,96,24,"��������",24,0);break;
		case 2:Show_Str(54,198,96,24,"��������",24,0);break;
		case 3:Show_Str(54,198,96,24,"��������",24,0);break;
		case 4:Show_Str(54,198,96,24,"��������",24,0);break;
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}
void xian_shi4(u8 result)
{
	switch(result)
	{
		case 6:LCD_ShowxNum(54,198,6,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 7:LCD_ShowxNum(54,198,7,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 8:LCD_ShowxNum(54,198,8,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 9:LCD_ShowxNum(54,198,9,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		case 10:LCD_ShowxNum(54,198,0,4,24,0);LCD_Fill(102,198,150,222,WHITE);break;
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}

*/





/*void xian_shi(u8 result)
{
	switch(result)
	{
		case 1:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,48,24,"ʯͷ",24,0);break;
		case 2:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,48,24,"����",24,0);break;
		case 3:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,48,24,"��  ",24,0);break;
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}
void xian_shi2(u8 result)
{
	switch(result)
	{
		case 4:LCD_Fill(54,198,150,222,WHITE);LCD_ShowxNum(54,198,1,1,24,0);break;
		case 5:LCD_Fill(54,198,150,222,WHITE);LCD_ShowxNum(54,198,2,1,24,0);break;
		case 6:LCD_Fill(54,198,150,222,WHITE);LCD_ShowxNum(54,198,3,1,24,0);break;
		case 7:LCD_Fill(54,198,150,222,WHITE);LCD_ShowxNum(54,198,4,1,24,0);break;
		case 8:LCD_Fill(54,198,150,222,WHITE);LCD_ShowxNum(54,198,5,1,24,0);break;
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}
void xian_shi3(u8 result)
{
	switch(result)
	{
		case 1:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"��������",24,0);break;
		case 2:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"��������",24,0);break;
		case 3:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"��������",24,0);break;
		case 4:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"��������",24,0);break;
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}*/




