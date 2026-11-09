#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint16_t machineNumber = 0x00; //设备编号
uint8_t liquidState = 0; //管内的液体状态

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	PWM_Init(); 
	IC_Init();			//输入捕获初始化
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Device:");
	OLED_ShowNum(1, 9, machineNumber, 2); // 显示设备编号

	OLED_ShowString(2, 1, "Freq:00000Hz"); //显示空白字符串
	PWM_SetPrescaler(360-1); //设置频率为2KHz
	PWM_SetCompare1(50); //使PWM以一半的占空比输出
	
	while (1)
	{
		OLED_ShowNum(2, 6, IC_GetFreq(), 5);	//不断刷新显示输入捕获测得的频率(TIM3/PA6)
	}
}
