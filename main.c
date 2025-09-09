#include "tm4c123gh6pm.h"
#include <stdint.h>

#define STCTRL_R (*(volatile uint32_t *)0xE000E010)
#define STRELOAD_R (*(volatile uint32_t *)0xE000E014)
#define STCURRENT_R (*(volatile uint32_t *)0xE000E018)

#define BLUE_LED (1<<2)

void portf_init();
int main(void)
{
    portf_init();

    STCURRENT_R = 0;
    STRELOAD_R = 500* 16000;
    STCTRL_R = 7;


	return 0;


}


void portf_init()
{
   SYSCTL_RCGC2_R |= 0x00000020;//Enable GPIO

   GPIO_PORTF_LOCK_R = 0x4C4F434B;
   GPIO_PORTF_CR_R = 0x1F;

   GPIO_PORTF_DEN_R |= 0x1F;
   GPIO_PORTF_DIR_R |= 0x0E;

   GPIO_PORTF_PUR_R = 0x11;

   GPIO_PORTF_DATA_R = 0x00;
}

void SysTickHandler(void)
{
    GPIO_PORTF_DATA_R ^= BLUE_LED;
}
