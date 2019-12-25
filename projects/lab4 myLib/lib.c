#include "lib.h"
#include "main.h"

void init_led(Ports port)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	if (port == PA8)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	}
	if (port == PA9)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	}
	if (port == PA10)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	}
	if (port == PD12)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	}
	if (port == PD13)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	}
	if (port == PD14)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	}
	if (port == PD15)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	}
}

void init_button(Ports port)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  

	if (port == PE0)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	}
	if (port == PE1)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;    
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	}
	if (port == USER_BUTTON)
	{
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;    
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	}
}	

void init_led_pwm(Ports port)
{
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	GPIO_InitTypeDef GPIO_Init_LED;
	TIM_OCInitTypeDef Hard_PWM_ini;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	if (port == PA8)
	{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 0;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;	
	TIM_TimeBaseInit(TIM1, &TIM_Time_user);
	
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	GPIO_Init(GPIOA, &GPIO_Init_LED);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	
	Hard_PWM_ini.TIM_OCMode = TIM_OCMode_PWM1;
	Hard_PWM_ini.TIM_OutputState = TIM_OutputState_Enable;
	Hard_PWM_ini.TIM_Pulse = 0;
	Hard_PWM_ini.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM1, &Hard_PWM_ini);	
	
	TIM_Cmd(TIM1, ENABLE);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);	
	}
	if (port == PA9)
	{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 0;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;	
	TIM_TimeBaseInit(TIM1, &TIM_Time_user);
	
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	GPIO_Init(GPIOA, &GPIO_Init_LED);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	
	Hard_PWM_ini.TIM_OCMode = TIM_OCMode_PWM1;
	Hard_PWM_ini.TIM_OutputState = TIM_OutputState_Enable;
	Hard_PWM_ini.TIM_Pulse = 0;
	Hard_PWM_ini.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM1, &Hard_PWM_ini);	
	
	TIM_Cmd(TIM1, ENABLE);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);	
	}
	if (port == PA10)
	{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 0;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;	
	TIM_TimeBaseInit(TIM1, &TIM_Time_user);
	
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	GPIO_Init(GPIOA, &GPIO_Init_LED);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
	
	Hard_PWM_ini.TIM_OCMode = TIM_OCMode_PWM1;
	Hard_PWM_ini.TIM_OutputState = TIM_OutputState_Enable;
	Hard_PWM_ini.TIM_Pulse = 0;
	Hard_PWM_ini.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC3Init(TIM1, &Hard_PWM_ini);	
	
	TIM_Cmd(TIM1, ENABLE);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);	
	}
}

void timer_ini(void)
{

	TIM_TimeBaseInitTypeDef TIM_Time_user;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 42000-1;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TIM_Time_user);
	
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);

}

bool press_button(Ports port)
{
	uint16_t c = TIM_GetCount(TIM2);
	if (port == PE0)
	{
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 0)
	return 1;
	else return 0;
	}
	if (port == PE1)
	{
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 0)
	return 1;
	else return 0;
	}
}

void change_color(Ports red_port, Ports green_port, Ports blue_port, Colors color)
{
	if (red_port == PA8)
	{
		if (green_port == PA9)
		{
			if (blue_port == PA10)
			{
				if (color == RED)
				{
				TIM_SetCompare1(TIM1, 1000);
				TIM_SetCompare2(TIM1, 0);
				TIM_SetCompare3(TIM1, 0);
				}
			}
		}
	}
	if (red_port == PA8)
	{
		if (green_port == PA9)
		{
			if (blue_port == PA10)
			{
				if (color == GREEN)
				{
				TIM_SetCompare1(TIM1, 0);
				TIM_SetCompare2(TIM1, 1000);
				TIM_SetCompare3(TIM1, 0);
				}
			}
		}
	}
	if (red_port == PA8)
	{
		if (green_port == PA9)
		{
			if (blue_port == PA10)
			{
				if (color == BLUE)
				{
				TIM_SetCompare1(TIM1, 0);
				TIM_SetCompare2(TIM1, 0);
				TIM_SetCompare3(TIM1, 1000);
				}
			}
		}
	}
	if (red_port == PA8)
	{
		if (green_port == PA9)
		{
			if (blue_port == PA10)
			{
				if (color == WHITE)
				{
				TIM_SetCompare1(TIM1, 1000);
				TIM_SetCompare2(TIM1, 1000);
				TIM_SetCompare3(TIM1, 1000);
				}
			}
		}
	}
	if (red_port == PA8)
	{
		if (green_port == PA9)
		{
			if (blue_port == PA10)
			{
				if (color == YELLOW)
				{
				TIM_SetCompare1(TIM1, 700);
				TIM_SetCompare2(TIM1, 1000);
				TIM_SetCompare3(TIM1, 0);
				}
			}
		}
	}
}

void flash_led(Ports port)
{
	if (port == PD12)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_12);
	}
	if (port == PD13)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_13);
	}
	if (port == PD14)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_14);
	}
	if (port == PD15)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_15);
	}
}





