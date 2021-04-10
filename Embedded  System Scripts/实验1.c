#include"stm32f10x.h"

void LED0_Config(void);
void LED0_On(void);
void LED0_Off(void);
void Delay(unsigned long x);

int main(void)
{
	LED0_Config();
	while(1)
	{
		LED0_On();
		Delay(226);
		LED0_Off();
		Delay(226);
	}
}

void LED0_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
	
void LED0_On(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void LED0_Off(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

void Delay(unsigned long x)
{
	unsigned long i;
	for(i=0;i<x;i++);
}