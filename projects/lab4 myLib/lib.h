#ifndef LIB_H
#define LIB_H

typedef enum Ports
{
	PA8,
	PA9,
	PA10,
	PE0, 
	PE1,
	USER_BUTTON,
	PD12,
	PD13,
	PD14,
	PD15
} Ports;

typedef enum Colors
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	YELLOW
	
} Colors;

#include "main.h"
#include <stdbool.h> 

void init_led(Ports port);
void init_button(Ports port);
void init_led_pwm(Ports port);
void timer_ini(void);
bool press_button(Ports port);
void change_color(Ports red_port, Ports green_port, Ports blue_port, Colors color);
void flash_led(Ports port);


#include <math.h>

#endif