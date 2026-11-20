#include "stm32f10x.h"                  // Device header
#include "pwm.h"


void Servo1_Init(void)
{
	PWM1_Init();
}

void Servo1_SetAngle(float Angle)
{
	PWM_SetCompare2(Angle / 180 *2000 +500);
}

void Servo2_Init(void)
{
	PWM2_Init();
}

void Servo2_SetAngle(float Angle)
{
	PWM_SetCompare4(Angle / 180 *2000 +500);
}
