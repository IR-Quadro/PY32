#include "py32f0xx.h"
#include "system_py32f0xx.h"


/* Global variable */
volatile uint32_t msTick = 0;


/* Function prototypes */
void delay_ms(uint32_t ms);



int main (void)
{
	
 /* Configure SysTick timer to generate interrupt every 1 ms
  * SystemCoreClock / 1000 => 1 kHz SysTick interrupt
  */
	SysTick_Config(SystemCoreClock / 1000);
	
	while(1)
	{
		
	 /* Main loop
    * Application code can be placed here
    */
		
	}
}



/* SysTick interrupt handler
 * This function is called every 1 ms
 */
void SysTick_Handler(void)
{
	msTick++;
}



/* Blocking delay function in milliseconds
 * Uses SysTick-based millisecond counter
 */
void delay_ms(uint32_t ms)
{
	uint32_t start = msTick;
	
	/* Wait until the required number of milliseconds has passed */
	while((msTick - start) < ms);
}