#include "main.h"
#include "lib.h"


int main(void)
{
  	SystemCoreClockUpdate();
	int count = 0;
	timer_ini();

	init_led(PD12);
	init_led(PD13);
	init_led(PD14);
	init_led(PD15);


	while (1) 
	{
	if (TIM_GetCount(TIM2) == 999)
	count++;
	if (count >= 4)
		count = 0;
	}
 	switch (count)
	{
	case 0:
	{	
		flash_led(PD12);
		break;
	}
	case 1:
	{
		flash_led(PD13);		
		break;
	}	
	case 2:
	{
		flash_led(PD14);
		break;
	}	
	case 3:
	{
		flash_led(PD15);
		break;
	}
	
	}
}


