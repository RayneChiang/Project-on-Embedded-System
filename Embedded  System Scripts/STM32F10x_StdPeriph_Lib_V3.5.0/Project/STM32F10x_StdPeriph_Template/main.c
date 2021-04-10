#include "stm32f10x.h"
#include<stdio.h>
#define ITM_Port8(n)   (*((volatile unsigned char*)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)  (*((volatile unsigned long*)(0xE0000000+4*n)))
#define DEMCR          (*((volatile unsigned long*)(0xE0000000+4*n)))
#DEFINE TRCENA         0x01000000
struct__FILE{int handle;};
FILE__stdout;
FILE__stdin;
int fputc(int ch,FILE *f)
{
	if(DEMCR&TRCENA)
	{
		while(ITM_Port32(0)==0);
		ITM_Port8(0)=ch;
	}
	return(ch);
}
void NCIV_Config(void);
void TIM2_Config(void);
void ADC1_Config(void);
volatile unsigned char acd1_flag;
volatile unsigned char adc1_value=0xAAA;
volatile float voltage_PB0=1.0;
int main(void)
{
	NVIC_Config();
	TIM1_Config();
	ADC1_Config();
	adc1_flag=0;
	while(1)
{
	if(adc1_flag)
	{
	adc1_value=ADC_GetConversionValue(ADC1);
	voltage_PB0=(float)adc1_value/4096*3.3;
	printf("%f\n",voltage_PB0);
	adc1_flag=0;
	}
}
}
void NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIV_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NIVC_InitStrcuture);
}
void TIM2_Config()
{
	TIM_TimeBseInitTypeDef TIM_TimeBseStructure;
	RCC_APB1PeriphColckCme(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler=36000-1;
	TIM_TimeBaseStructure.TIM_Period=9000-1;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBseStructure)
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIN_Cmd(TIM2,ENABLE);
}]
void ADC1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB);
	GPIO_InitSturcture.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_AIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PLCK2_Div6);
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC._ScanConvMode=ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1,ENABLE)
	ADC_ResetCalibaration(ADC1)
	while(ADC_GetResetCalibaration(ADC1));
	ADC_StartCalibaration(ADC1);
	while(ADC_GetCalibarationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}