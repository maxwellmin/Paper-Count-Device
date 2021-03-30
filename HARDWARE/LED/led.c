#include "led.h"
#include "delay.h"

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
}
 
void KEY16_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //使能PB,PE端口时钟
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
									|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 //第一行
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);						 //PB.5 输出高
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);	
}

u8 KEY_Scan_Row(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;				 //第一行
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //输入上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	    		 //第一列
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);
	
	if(ROW1 == 0)
	{
		delay_ms(10);//去抖动 
		if(ROW1 == 0)
		{
			return 1;
		}
	}
	else if(ROW2 == 0)
	{
		delay_ms(10);//去抖动 
		if(ROW2 == 0)
		{
			return 2;
		}
	}
	else if(ROW3 == 0)
	{
		delay_ms(10);//去抖动 
		if(ROW3 == 0)
		{
			return 3;
		}
	}
	else if(ROW4 == 0)
	{
		delay_ms(10);//去抖动 
		if(ROW4 == 0)
		{
			return 4;
		}
	}
	else 
	{
		return 0;
	}
	return 0;
}

u8 KEY_Scan_Column(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 //第一行
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //输入上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	    		 //第一列
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);
	
	
	if(COLUMN1 == 0)
	{
		delay_ms(10);//去抖动 
		if(COLUMN1 == 0)
		{
			return 1;
		}
	}
	else if(COLUMN2 == 0)
	{
		delay_ms(10);//去抖动 
		if(COLUMN2 == 0)
		{
			return 2;
		}
	}
	else if(COLUMN3 == 0)
	{
		delay_ms(10);//去抖动 
		if(COLUMN3 == 0)
		{
			return 3;
		}
	}
	else if(COLUMN4 == 0)
	{
		delay_ms(10);//去抖动 
		if(COLUMN4 == 0)
		{
			return 4;
		}
	}
	else 
	{
		return 0;
	}
	return 0;
}

u8 KEY16_Scan(void)
{
	static u8 key_up=1;//按键按松开标志
	u8 row = 0 , column = 0;
	row = KEY_Scan_Row();
	column =  KEY_Scan_Column();
	if(key_up&&row>0&&column>0)
	{
		key_up=0;
		if(row>0&&column>0)return (row-1)*4+column;
	}else if(row == 0 || column == 0)key_up=1;
		return 0;//无按键按下
}

/////////////////////////////////////////////////////////////
//***************************************2222************************************************//
u32 KeyPinX[4]={KX1,KX2,KX3,KX4};
u32 KeyPinY[4]={KY1,KY2,KY3,KY4};
//u8 key_dowm_falg = 0;

//void GPIO_Key2(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructuress;  
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);           //打开时钟    
//	
//	GPIO_InitStructuress.GPIO_Pin = KX1|KX2|KX3|KX4;  //初始化PD0-PD3  
//	GPIO_InitStructuress.GPIO_Mode = GPIO_Mode_OUT ;        
//	GPIO_InitStructuress.GPIO_OType = GPIO_OType_PP;                                             //设置为推挽输出  
//	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;  
//	GPIO_InitStructuress.GPIO_PuPd =GPIO_PuPd_UP;                //上拉  
//	GPIO_Init(KeyX_PORT, &GPIO_InitStructuress);   

//	GPIO_InitStructuress.GPIO_Pin =KY1|KY2|KY3|KY4;    //初始化PD4-PD7  
//	GPIO_InitStructuress.GPIO_Mode =GPIO_Mode_OUT ;  
//	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;  
//	GPIO_InitStructuress.GPIO_PuPd = GPIO_PuPd_DOWN ;            //下拉  
//	GPIO_Init(KeyY_PORT, &GPIO_InitStructuress);   
//	
//	GPIO_SetBits( KeyX_PORT,KX1|KX2|KX3|KX4);  
//	GPIO_ResetBits( KeyY_PORT,KY1|KY2|KY3|KY4);
//}
u8 Read_KeyValue2(void)
{
	u8 key_val=0,key=0,i,j;
	for(i=0;i<4;++i)
	{
		GPIO_SetBits(KeyX_PORT,KeyPinX[i]);
		for(j=0;j<4;++j)
		{	
			if	(GPIO_ReadInputDataBit(KeyY_PORT,KeyPinY[j])==Bit_SET)
			{
				delay_ms(10);
				if(	GPIO_ReadInputDataBit(KeyY_PORT,KeyPinY[j])==Bit_SET)
				{
					key = j+1+i*4;
					while(GPIO_ReadInputDataBit(KeyY_PORT,KeyPinY[j])==Bit_SET);
//					key_dowm_falg = 1;
					GPIO_ResetBits(KeyX_PORT,KeyPinX[i]);
				}
			}
		}
		GPIO_ResetBits(KeyX_PORT,KeyPinX[i]);
	}
	switch(key)
	{
		case 1: key_val =   1;break;
		case 2: key_val =   2;break;
		case 3: key_val =   3;break;
		case 4: key_val =   4;break;
		case 5: key_val =   5;break;
		case 6: key_val =   6;break;
		case 7: key_val =   7;break;
		case 8: key_val =   8;break;
		case 9: key_val =   9;break;
		case 10:key_val =  10;break;
		case 11:key_val =  11;break;
		case 12:key_val =  12;break;
		case 13:key_val =  13;break;
		case 14:key_val =  14;break;
		case 15:key_val =  15;break;
		case 16:key_val =  16;break;
		default:key_val =   0;break;
	}
	return key_val;
}




