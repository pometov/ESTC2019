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
	
	int SWITCH_DELAY = 50000;
	int count = 0;

  	gpio_ini();

	while (1) 
	{

     
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 0)
	{
        	RCC->CR |= RCC_CR_HSEON;
		while((RCC->CR & RCC_CR_HSERDY) == 0);
   		RCC->CFGR &=~RCC_CFGR_SW; 
  		RCC->CFGR |= RCC_CFGR_SW_HSE;
		RCC->CR |= RCC_CR_PLLON;
		while((RCC->CR & RCC_CR_PLLRDY) == 0);
		RCC->CFGR |= RCC_CFGR_SW_PLL;

	
	}

	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 0)
	{
		RCC->CR |= RCC_CR_HSION;
		while((RCC->CR & RCC_CR_HSIRDY) == 0);
	   	RCC->CFGR &=~RCC_CFGR_SW; 
	  	RCC->CFGR |= RCC_CFGR_SW_HSI;
		RCC->CR |= RCC_CR_PLLON;
		while((RCC->CR & RCC_CR_PLLRDY) == 0);
		RCC->CFGR |= RCC_CFGR_SW_PLL;
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
	{
	count++;
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 );
	if (count >= 3)
		count = 0;
	}
	switch (count)
	{
	case 0:
	{
     		int i;

		GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 );
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		

     		for (i = 0; i < SWITCH_DELAY; i++);
     		GPIO_SetBits(GPIOD, GPIO_Pin_12 );
     		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_13 );
     		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_14 );
     		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
     		for (i = 0; i < SWITCH_DELAY; i++);

		break;
	}
	case 1:
	{
     		int i;	

	        for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15 );
		GPIO_SetBits(GPIOD, GPIO_Pin_12 );
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 );
		GPIO_SetBits(GPIOD, GPIO_Pin_13 );
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13 );
		GPIO_SetBits(GPIOD, GPIO_Pin_14 );
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14 );
		GPIO_SetBits(GPIOD, GPIO_Pin_15 );
		
		break;
	}
	case 2:
	{

     		int i;
     	
	        for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_ResetBits(GPIOA, GPIO_Pin_10 );
		GPIO_SetBits(GPIOA, GPIO_Pin_8 );
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_ResetBits(GPIOA, GPIO_Pin_8 );
		GPIO_SetBits(GPIOA, GPIO_Pin_9 );
		for (i = 0; i < SWITCH_DELAY; i++);
		GPIO_ResetBits(GPIOA, GPIO_Pin_9 );
		GPIO_SetBits(GPIOA, GPIO_Pin_10 );
		
		break;
	}


	}
	}
}


