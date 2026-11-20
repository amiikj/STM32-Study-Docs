#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "servo.h"
#include "Delay.h"
#include "key.h"
#include "ad.h"

uint16_t KeyNum;
float Angle_X;
float Angle_Y = 180;
float Angle_X_Direction=0;
float Angle_Y_Direction=0;
uint16_t ADM=10000;
uint16_t AD2;
uint16_t a=180 ;
int main(void)
{
	OLED_Init();
	Servo1_Init();
	Servo2_Init();
	Key_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"Angle_Y_Dir:");
	OLED_ShowString(2,1,"Angle_X_Dir:");
	OLED_ShowString(3,1,"Angle_Y:");
	OLED_ShowString(4,1,"AD2:");
	while (1) 
    {
		Angle_X ++;
		AD2=AD_GetValue(ADC_Channel_2);
		
		Servo1_SetAngle(Angle_X);
		Delay_ms(10);
		if (AD2<ADM)
		{
		 ADM=AD2;
		 Angle_X_Direction = Angle_X;
		 Angle_Y_Direction = Angle_Y;
		}
		
		if (Angle_X > 180)
		{
			Angle_X = 0;
			a-=30;
			Servo1_SetAngle(Angle_X);
			OLED_ShowNum(2,13,Angle_X_Direction,3);
			Delay_ms(1000);
			while (Angle_Y>a)
			{
				Angle_Y --;
				Servo2_SetAngle(Angle_Y);
				Delay_ms(50);
				OLED_ShowNum(3,9,Angle_Y,3);
			}
			
		}
		if (AD2<ADM)
		{
		 ADM=AD2;
		 Angle_X_Direction = Angle_X;
		 Angle_Y_Direction = Angle_Y;
		}
		if (Angle_Y<90)
		{
			Servo1_SetAngle(Angle_X_Direction);
			Delay_ms(2000);
			Servo2_SetAngle(Angle_Y_Direction);
			Delay_ms(3000);
			ADM=10000;
			Angle_Y=180;
			a=180;
		}
		
		
		OLED_ShowNum(1,13,Angle_Y_Direction,3);
		OLED_ShowNum(3,9,Angle_Y,3);
		OLED_ShowNum(4,5,AD2,3);
		
		
	}
}
