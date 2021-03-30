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

float res1,res2;//中断读取值
float temp1,temp2,X1,X2;//初始值
float re1,re2;
float data1[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//判决值
float data2[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float info1[100];
float info2[100];
int dire1[100];
int dire2[100];
int main(void)
{
	Sys_Init();//函数初始化	
	///////////////////发挥增加//////////////
//	X1=res1-res3;//左右两块的初始差值
//	X2=res2-res0;//上下两块初始差值
///////////////////////汉字挂载//////////////////////////////////////////////////
	 while(font_init()) 		//检查字库
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//清除显示	     
		delay_ms(200);				  
	}
/////////////////////////汉字挂载完毕，主程序/////////////////////////////////汉字16*16/12*12/24*24	 
  POINT_COLOR=RED;       
	Show_Str(6,6,224,16,"2019TI杯大学生电子设计竞赛",16,0);
	Show_Str(6,22,144,16,"F题：纸张计数显示装置",16,0);
	Show_Str(6,38,48,16,"按键:",16,0);
	Show_Str(6,54,80,16,"工作模式:",16,0);
	Show_Str(6,70,80,16,"训练方向:",16,0);
	Show_Str(6,86,48,16,"当前:",16,0);
	Show_Str(6,102,96,16,"CH1:00000.00",16,0);
	Show_Str(6,118,96,16,"初1:00000.00",16,0);
	Show_Str(6,134,96,16,"CH2:00000.00",16,0);
	Show_Str(6,150,96,16,"初2:00000.00",16,0);
	Show_Str(6,198,96,48,"纸张数:",48,0);
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
				case 1: Show_Str(86,54,96,16,"训练 ",16,0);gongzuo=0;gongzuo2=0;fahui1=0;flag1=0;zengjia=0;jianshao=0;BEEP=0;break;
				case 2: Show_Str(86,54,96,16,"测量",16,0);
								gongzuo=1;gongzuo2=0;fahui1=0;flag1=0;zengjia=0;jianshao=0;dazhao=1;
								BEEP=1;
								delay_ms(1000);//延时500ms
								BEEP=0;		
								break;
				case 3: Show_Str(86,70,96,16,"加1 ",16,0);zengjia=1;gongzuo=0;gongzuo2=0;fahui1=0;flag1=0;BEEP=0;break;
				case 4: Show_Str(86,70,96,16,"减1 ",16,0);jianshao=1;gongzuo=0;gongzuo2=0;fahui1=0;flag1=0;BEEP=0;break;
				case 5: Show_Str(86,54,96,16,"学习",16,0);gongzuo=0;gongzuo2=0;fahui1=0;xuexi=1;zengjia=0;jianshao=0;BEEP=0;break;
				case 9: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"2张纸",16,0);number=2;flag=1;BEEP=0;break;
				case 13:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"3张纸",16,0);number=3;flag=1;BEEP=0;break;
				case 6: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"4张纸",16,0);number=4;flag=1;BEEP=0;break;
				case 7: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"5张纸",16,0);number=5;flag=1;BEEP=0;break;
				case 8: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"6张纸",16,0);number=6;flag=1;BEEP=0;break;
				case 10:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"7张纸",16,0);number=7;flag=1;BEEP=0;break;
				case 11:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"8张纸",16,0);number=8;flag=1;BEEP=0;break;
				case 12:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"9张纸",16,0);number=9;flag=1;BEEP=0;break;
				case 14:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"10张纸",16,0);number=10;flag=1;BEEP=0;break;
				case 15:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"进位",16,0);number=12;flag=1;BEEP=0;break;
				case 16:Show_Str(86,54,96,16,"计数",16,0);gongzuo=0;gongzuo2=0;fahui1=1;flag1=1;fahui3=1;break;
				default:flag=0;break;
			}
		}
		
		LCD_ShowxNum(38,102,res1*500,5,16,0);re1=res1;LCD_ShowxNum(86,102,(res1-re1)*100,2,16,0);
		LCD_ShowxNum(38,118,temp1*500,5,16,0);re1=res1;LCD_ShowxNum(86,118,(res1-re1)*100,2,16,0);
		LCD_ShowxNum(38,134,res2*500,5,16,0);re2=res2;LCD_ShowxNum(86,134,(res2-re2)*100,2,16,0);
		LCD_ShowxNum(38,150,temp2*500,5,16,0);re2=res2;LCD_ShowxNum(86,150,(res2-re2)*100,2,16,0);
//		LCD_ShowxNum(38,246,temp0*100,5,16,0);LCD_ShowxNum(38,262,temp1*100,5,16,0);
//		LCD_ShowxNum(38,278,temp2*100,5,16,0);LCD_ShowxNum(38,294,temp3*100,5,16,0);	
		
		if(gongzuo)//测量--------------------------------
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
		{		if(!fahui1)//训练-----------------------------
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
				
/*				else//发挥1----------------------------------
				{ if(!fahui3)
					{
						if(flag1)
						{
							//发挥1
							if(res1-(res3+X1)>1.5)
							{//从左往右
								result = 1;
								delay_ms(1000);delay_ms(1000);
							}
							else if((res3+X1)-res1>1.5)//从右往左
								{
									result=2;delay_ms(1000);delay_ms(1000);
								}
								else if(res2-(res0+X2)>1.5)//从上往下
									{
										result=3;
										delay_ms(1000);delay_ms(1000);
									}else if((res0+X2)-res2>1.5)//从下往上
									{
										result=4;
										delay_ms(1000);delay_ms(1000);
									}
									xian_shi3(result);
									delay_ms(500);delay_ms(500);
									delay_ms(500);delay_ms(500);
						}
					}
					else//发挥3----------------------------------
					{ result=pan_jue5();xian_shi4(result); }
					
				}//发挥12
*/
			}//训练
		}//判决1、2
		
	}


void Sys_Init(void)
{
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	usmart_dev.init(72);		//初始化USMART		
// 	LED_Init();		  			//初始化与LED连接的硬件接口
//	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD   
	BEEP_Init();         	//初始化蜂鸣器端口
	W25QXX_Init();				//初始化W25Q128
 	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
	
	KEY16_Init();
	while(FDC2214_Init())
		LCD_ShowString(30,50,200,16,16,"FDC2214 Error!");
	LCD_Fill(30,50,142,66,WHITE);
	
	delay_ms(100);
	temp1 = Cap_Calculate(0);//读取初始值
//	temp1 = Cap_Calculate(1);
	temp2 = Cap_Calculate(2);
//	temp3 = Cap_Calculate(3);
	TIM5_Ctrl_Init(2000-1,720-1);
}

//定时器5中断服务程序
void TIM5_IRQHandler(void)   //TIM5中断
{
	if(TIM5->SR&0X0001)//20ms定时中断
 {
	res1 = Cap_Calculate(0);//采集数据
//	res1 = Cap_Calculate(1);
	res2 = Cap_Calculate(2);
//	res3 = Cap_Calculate(3);
//	Data_Send_Status(res,0,0);
//	printf("%5d : %5d : %5d\r\n",res0,res1,res2);
//	 led=~led;
 }
 TIM5->SR&=~(1<<0);  //中断标志位清0，等待下一次中断
}
//********************判决***************************//
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

//********************训练***************************//
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

//********************显示***************************//
void xian_shi(u8 result)
{
	switch(result)
	{
		case 0:Show_Str(54,198,96,24,"极板打开",24,0);break;
		case 1:Show_Str(54,198,96,24,"  1张    ",24,0);break;
		case 2:Show_Str(54,198,96,24,"  2张    ",24,0);break;
		case 3:Show_Str(54,198,96,24,"  3张    ",24,0);break;
		case 4:Show_Str(54,198,96,24,"  4张    ",24,0);break;
		case 5:Show_Str(54,198,96,24,"  5张    ",24,0);break;
		case 6:Show_Str(54,198,96,24,"  6张    ",24,0);break;
		case 7:Show_Str(54,198,96,24,"  7张    ",24,0);break;
		case 8:Show_Str(54,198,96,24,"  8张    ",24,0);break;
		case 9:Show_Str(54,198,96,24,"  9张    ",24,0);break;
		case 10:Show_Str(54,198,96,24,"  10张   ",24,0);break;
		case 11:Show_Str(54,198,96,24,"  11张   ",24,0);break;
		case 12:Show_Str(54,198,96,24,"  12张   ",24,0);break;
		case 13:Show_Str(54,198,96,24,"  13张   ",24,0);break;
		case 14:Show_Str(54,198,96,24,"  14张   ",24,0);break;
		case 15:Show_Str(54,198,96,24,"  15张   ",24,0);break;
		case 16:Show_Str(54,198,96,24,"  16张   ",24,0);break;
		case 17:Show_Str(54,198,96,24,"  17张   ",24,0);break;
		case 18:Show_Str(54,198,96,24,"  18张   ",24,0);break;
		case 19:Show_Str(54,198,96,24,"  19张   ",24,0);break;
		case 20:Show_Str(54,198,96,24,"  20张   ",24,0);break;
		case 21:Show_Str(54,198,96,24,"  21张   ",24,0);break;
		case 22:Show_Str(54,198,96,24,"  22张   ",24,0);break;
		case 23:Show_Str(54,198,96,24,"  23张   ",24,0);break;
		case 24:Show_Str(54,198,96,24,"  24张   ",24,0);break;
		case 25:Show_Str(54,198,96,24,"  25张   ",24,0);break;
		case 26:Show_Str(54,198,96,24,"  26张   ",24,0);break;
		case 27:Show_Str(54,198,96,24,"  27张   ",24,0);break;
		case 28:Show_Str(54,198,96,24,"  28张   ",24,0);break;
		case 29:Show_Str(54,198,96,24,"  29张   ",24,0);break;
		case 30:Show_Str(54,198,96,24,"  30张   ",24,0);break;
		case 31:Show_Str(54,198,96,24,"  31张   ",24,0);break;
		case 32:Show_Str(54,198,96,24,"  32张   ",24,0);break;
		case 33:Show_Str(54,198,96,24,"  33张   ",24,0);break;
		case 34:Show_Str(54,198,96,24,"  34张   ",24,0);break;
		case 35:Show_Str(54,198,96,24,"  35张   ",24,0);break;
		case 36:Show_Str(54,198,96,24,"  36张   ",24,0);break;
		case 37:Show_Str(54,198,96,24,"  37张   ",24,0);break;
		case 38:Show_Str(54,198,96,24,"  38张   ",24,0);break;
		case 39:Show_Str(54,198,96,24,"  39张   ",24,0);break;
		case 40:Show_Str(54,198,96,24,"  40张   ",24,0);break;
		case 41:Show_Str(54,198,96,24,"  41张   ",24,0);break;
		case 42:Show_Str(54,198,96,24,"  42张   ",24,0);break;
		case 43:Show_Str(54,198,96,24,"  43张   ",24,0);break;
		case 44:Show_Str(54,198,96,24,"  44张   ",24,0);break;
		case 45:Show_Str(54,198,96,24,"  45张   ",24,0);break;
		case 46:Show_Str(54,198,96,24,"  46张   ",24,0);break;
		case 47:Show_Str(54,198,96,24,"  47张   ",24,0);break;
		case 48:Show_Str(54,198,96,24,"  48张   ",24,0);break;
		case 49:Show_Str(54,198,96,24,"  49张   ",24,0);break;
		case 50:Show_Str(54,198,96,24,"  50张   ",24,0);break;
		case 51:Show_Str(54,198,96,24,"  51张   ",24,0);break;
		case 52:Show_Str(54,198,96,24,"  52张   ",24,0);break;
		case 53:Show_Str(54,198,96,24,"  53张   ",24,0);break;
		case 54:Show_Str(54,198,96,24,"  54张   ",24,0);break;
	  case 55:Show_Str(54,198,96,24,"  55张   ",24,0);break;
		case 56:Show_Str(54,198,96,24,"  56张   ",24,0);break;
		case 57:Show_Str(54,198,96,24,"  57张   ",24,0);break;
		case 58:Show_Str(54,198,96,24,"  58张   ",24,0);break;
		case 59:Show_Str(54,198,96,24,"  59张   ",24,0);break;
		case 60:Show_Str(54,198,96,24,"  60张   ",24,0);break;
		case 61:Show_Str(54,198,96,24,"  61张   ",24,0);break;
		case 62:Show_Str(54,198,96,24,"  62张   ",24,0);break;
		case 63:Show_Str(54,198,96,24,"  63张   ",24,0);break;
		case 64:Show_Str(54,198,96,24,"  64张   ",24,0);break;
		case 65:Show_Str(54,198,96,24,"  65张   ",24,0);break;
		case 66:Show_Str(54,198,96,24,"  66张   ",24,0);break;
		case 67:Show_Str(54,198,96,24,"  67张   ",24,0);break;
		case 68:Show_Str(54,198,96,24,"  68张   ",24,0);break;
		case 69:Show_Str(54,198,96,24,"  69张   ",24,0);break;
		case 70:Show_Str(54,198,96,24,"  70张   ",24,0);break;
		case 99:Show_Str(54,198,96,24,"极板短路",24,0);break;	
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
		case 1:Show_Str(54,198,96,24,"从左往右",24,0);break;
		case 2:Show_Str(54,198,96,24,"从右往左",24,0);break;
		case 3:Show_Str(54,198,96,24,"从上往下",24,0);break;
		case 4:Show_Str(54,198,96,24,"从下往上",24,0);break;
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
		case 1:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,48,24,"石头",24,0);break;
		case 2:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,48,24,"剪刀",24,0);break;
		case 3:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,48,24,"布  ",24,0);break;
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
		case 1:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"从左往右",24,0);break;
		case 2:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"从右往左",24,0);break;
		case 3:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"从上往下",24,0);break;
		case 4:LCD_Fill(54,198,150,222,WHITE);Show_Str(54,198,96,24,"从下往上",24,0);break;
		default:LCD_Fill(54,198,150,222,WHITE);break;
	}
}*/




