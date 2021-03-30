#include "ssy.h"
#include "led.h"
#include "lcd.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
//-------------------------------------------------------------------------------------------------------------------
//  @brief      绝对值函数
u16 myabs(int dat)
{
    if(dat>=0)  return dat;
    else        return -dat;
}
float myabsf(float dat)
{
    if(dat>=0)  return dat;
    else        return -dat;
}
//-------------------------------------------------------------------------------------------------------------------
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, DISABLE);  //使能TIMx					 
}
extern u8 key,keyval;
extern u8 gongzuo,youxi;
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			key=KEY16_Scan();//			key=Read_KeyValue2();
			if(key) 
			{
				LCD_ShowxNum(54,38,key,2,16,0);
				switch(key)
				{
					case 1: Show_Str(86,54,96,16,"训练",16,0);gongzuo=0;keyval=key;break;
					case 2: Show_Str(86,54,96,16,"测量",16,0);gongzuo=1;keyval=key;break;
					case 3: Show_Str(86,70,96,16,"猜拳",16,0);youxi=0;keyval=key;break;
					case 4: Show_Str(86,70,96,16,"划拳",16,0);youxi=1;keyval=key;break;
					case 5: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"1张纸",16,0);keyval=key;break;
					case 6: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"2张纸",16,0);keyval=key;break;
					case 7: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"3张纸",16,0);keyval=key;break;
//					case 7: 
//						LCD_Fill(54,86,86,102,WHITE);
//					Show_Str(54,86,96,16,"布",16,0);
//					keyval=key;
//					break;
									
				case 8: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"4张纸",16,0);keyval=key;break;
				case 9: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"5张纸",16,0);keyval=key;break;
				case 10:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"6张纸",16,0);keyval=key;break;
				case 11:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"7张纸",16,0);keyval=key;break;
				case 12:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,32,16,"8张纸",16,0);keyval=key;break;
					
//					case 7: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,96,16,"布",16,0);break;
//					case 8: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,96,16,"1",16,0);break;
//					case 9: LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,96,16,"2",16,0);break;
//					case 10:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,96,16,"3",16,0);break;
//					case 11:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,96,16,"4",16,0);break;
//					case 12:LCD_Fill(54,86,86,102,WHITE);Show_Str(54,86,96,16,"5",16,0);break;
//					case 13:zuobiao-=1;status=zuobiao+25;break;
//					case 14:zuobiao+=1;status=zuobiao+25;break;
//					case 15:zuobiao-=2;status=zuobiao+25;flag=1;TIM_SetCompare1(TIM11,1750);delay_ms(335);TIM_SetCompare1(TIM11,1350);delay_ms(385);break;
//					case 16:zuobiao+=2;status=zuobiao+25;flag=1;TIM_SetCompare1(TIM11,1750);delay_ms(335);TIM_SetCompare1(TIM11,1350);delay_ms(385);break;
				}
			}
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
}
//LCD_ShowxNum(54,86,1,1,16,0);

