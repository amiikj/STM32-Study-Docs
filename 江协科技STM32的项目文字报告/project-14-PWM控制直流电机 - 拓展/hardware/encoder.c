#include "stm32f10x.h"  // Device header


int16_t Encoder_Count;

void Encoder_Init(void)
{
/*记得用江协的PPT辅助理解*/
	/*第一步初始化四个原件的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	
	/*EXTI,NVIC的两个外设的时钟是不用开启的*/
	
	/*第二步GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_1  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						
	
	/*第三步AFIO外设中断引脚选择配置*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	/*第四步配置EXTI*/
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE ;
	EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt ;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	/*第五步配置NVIC*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	/*分组方式整个芯片只能用一种，所以最好放在主函数中*/
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI0_IRQHandler(void)/*若为15_10，则写在同一个函数里，用两个并列的 if */
{
	if (EXTI_GetITStatus(EXTI_Line0)== SET)	
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0) 
		{
			Encoder_Count --;
		
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1)== SET)	
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0) 
		{
			Encoder_Count ++;
		
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

int16_t Encoder_Get(void)
{
	int8_t temp = Encoder_Count;  //关键：temp的引入
	
	return temp;
	Encoder_Count = 0;
}
