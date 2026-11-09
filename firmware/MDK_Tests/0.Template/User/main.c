#include "stm32f10x.h"                  // Device header

void main(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //使用推挽输出
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz; //设置引脚速率
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13; //选中引脚
	GPIO_Init(GPIOC,&GPIOInitStruct);
	/*
	类似于
	PinMode(A13,OUTPUT);
	*/
	GPIO_SetBits(GPIOC,GPIO_Pin_13); //高电平
	// GPIO_ResetBits(GPIOC,GPIO_Pin_13); //低电平
	/*
	类似于
	DigitalWrite(A13,HIGH);
	*/
	
	while(1){
	}
}
