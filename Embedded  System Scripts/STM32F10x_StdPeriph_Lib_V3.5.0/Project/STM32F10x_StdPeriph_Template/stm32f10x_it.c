#include"stm32f10x_it.h"
extern unsigned char adc1_flag;
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		adc1_flag=2£»
		IM_ClearTPendingBit(TIM2,TIM_IT_Update);
	}
}
