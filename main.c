#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

extern void SystemInit(void);

int main(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_ClocksTypeDef RCC_ClockFreq;
	uint32_t i=0;

	SystemInit();

	/* This function fills the RCC_ClockFreq structure with the current
	     frequencies of different on chip clocks (for debug purpose) **************/
	RCC_GetClocksFreq(&RCC_ClockFreq);

	/* Output HSE clock on MCO1 pin(PA8) ****************************************/
	/* Enable the GPIOA peripheral */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure MCO1 pin(PA8) in alternate function */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* HSE clock selected to output on MCO1 pin(PA8)*/
	RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);

	/* Output SYS clock on MCO2 pin(Pc9) ****************************************/
	/* Enable the GPIOC peripheral */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Configure MCO1 pin(PA8) in alternate function */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* HSE clock selected to output on MCO1 pin(PC9)*/
	RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_1);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	while(1)
	{
		GPIOD->BSRRH = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIOD->BSRRL = GPIO_Pin_12;
		for(i=0;i<1000000;i++);
		GPIOD->BSRRH = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIOD->BSRRL = GPIO_Pin_13;
		for(i=0;i<1000000;i++);
		GPIOD->BSRRH = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIOD->BSRRL = GPIO_Pin_14;
		for(i=0;i<1000000;i++);
		GPIOD->BSRRH = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIOD->BSRRL = GPIO_Pin_15;
		for(i=0;i<1000000;i++);

	}
}
