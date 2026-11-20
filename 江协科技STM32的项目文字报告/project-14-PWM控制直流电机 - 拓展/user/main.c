#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "servo.h"
#include "Delay.h"
#include "key.h"
#include "motor.h"
#include "encoder.h"
int16_t Speed =0;



int main(void)
{
	OLED_Init();
	Servo_Init();
	Key_Init();
	Motor_Init();
	Encoder_Init();
	
	Speed = 0;
	
	OLED_ShowString(1,1,"Speed:");
	while (1) 
    {
		 Speed+=Encoder_Get();
		 if (Speed>100)
		 {
		 Speed =100;//关键锁定功能
		 }
		
		 if (Speed<-100)
		 {
		 Speed  =-100;
		 }
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1,7,Speed,4);
	}
}
