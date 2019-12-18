#include "main.h"


void gpio_ini(void) // Иницилизация
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  

  
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;  // Плата STM
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

/*	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; // Плата дополнительная
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  */

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;    // Кнопки дополнительной платы
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                                     
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;     // Кнопка          
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;            
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;       
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;          
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 
}

void pwm_power(void)   // Иницилизация ШИМ
{
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	GPIO_InitTypeDef GPIO_Init_LED;
	TIM_OCInitTypeDef Hard_PWM_ini;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 0;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM1, &TIM_Time_user);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_Init_LED);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
	
	Hard_PWM_ini.TIM_OCMode = TIM_OCMode_PWM1;
	Hard_PWM_ini.TIM_OutputState = TIM_OutputState_Enable;
	Hard_PWM_ini.TIM_Pulse = 0;
	Hard_PWM_ini.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	TIM_OC1Init(TIM1, &Hard_PWM_ini);	
	TIM_OC2Init(TIM1, &Hard_PWM_ini);
	TIM_OC3Init(TIM1, &Hard_PWM_ini);
	
	
	TIM_Cmd(TIM1, ENABLE);


	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);

/*	TIM_TimeBaseInitTypeDef TIM_Time_user;
	GPIO_InitTypeDef GPIO_Init_LED;
	TIM_OCInitTypeDef		Hard_PWM_ini;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 20 - 1;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM4, &TIM_Time_user);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD, &GPIO_Init_LED);
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
	
	Hard_PWM_ini.TIM_OCMode = TIM_OCMode_PWM1;
	Hard_PWM_ini.TIM_OutputState = TIM_OutputState_Enable;
	Hard_PWM_ini.TIM_Pulse = 999;
	Hard_PWM_ini.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC4Init(TIM4, &Hard_PWM_ini);
	
	
	TIM_Cmd(TIM4, ENABLE); */
	
}

int main(void)
{
  	SystemCoreClockUpdate();

  	gpio_ini();
	pwm_power();
	
/*	uint8_t i = 0;
	uint16_t j = 0; */

	uint16_t pwm1 = 0;
	uint16_t pwm2 = 0;
	uint16_t pwm3 = 0;
	uint16_t c = 0;
	int i = 0;

	while (1) {


/*	TIM_SetCompare4(TIM4, j);
	j++;
	if (j >= 1000) j=0;
	for (i = 0; i < SWITCH_DELAY; i++); */


	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 0)
	{
		c++;
		if (c>=3) c = 0;
		for (i = 0; i < 25000; i++);
	}

	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 0)
	{
		if (c == 0)
		{
			pwm1 = pwm1 +1;
			if (pwm1 >= 1000) pwm1 = 0;
			TIM_SetCompare1(TIM1, pwm1);
			for (i = 0; i < 25000; i++);
		}
		if (c == 1)
		{
			pwm2+=1;
			if (pwm2 >= 1000) pwm2 = 0;
			TIM_SetCompare2(TIM1, pwm2);
			for (i = 0; i < 25000; i++);
		}
		if (c == 2)
		{
			pwm3+=1;
			if (pwm3 >= 1000) pwm3 = 0;
			TIM_SetCompare3(TIM1, pwm3);
			for (i = 0; i < 25000; i++);
		}
	}
	}
}


