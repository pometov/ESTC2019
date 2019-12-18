#include "main.h"

int j = 0;

void TIM2_IRQHandler(void) // смена цветов диодов дополнительной платы по таймеру с использованием прерывания
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		flash_led();
	}
}

void timer_ini(void)   // Иницилизация таймера
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

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; // Плата дополнительная
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

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

int main(void)
{
  	SystemCoreClockUpdate();

	int count = 0;

  	gpio_ini();
	timer_ini();

	while (1) 
	{

	if (TIM_GetCount(TIM2) == 999)  // смена цветов диодов основной платы по таймеру без использывания прерывания
	{
	count++;
	if (count >= 4)
		count = 0;
	}
 	switch (count)
	{
	case 0:
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_12 );
		break;
	}
	case 1:
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_13 );
		break;
	}	
	case 2:
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_14 );
		break;
	}	
	case 3:
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
     		GPIO_SetBits(GPIOD, GPIO_Pin_15 );
		break;
	}
	
	}
}

void flash_led(void)
{
	j++;
	if (j >= 3)
		j = 0;

	switch (j)
	{
		case 0:
		{	
			GPIO_ResetBits(GPIOA, GPIO_Pin_10 );
			GPIO_SetBits(GPIOA, GPIO_Pin_8 );
			break;
		}
		case 1:
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_8 );
			GPIO_SetBits(GPIOA, GPIO_Pin_9 );
			break;
		}
		case 2:
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_9 );
			GPIO_SetBits(GPIOA, GPIO_Pin_10 );
			break;
		}
	}
	
}



