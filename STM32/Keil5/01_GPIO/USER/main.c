#include "stm32f10x.h"

void Delay_ms(uint16_t nms)
{	 		  	  
	 uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*9000;			
	SysTick->VAL =0x00;           			
	SysTick->CTRL=0x01 ;          			
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	  
	SysTick->CTRL=0x00;      	 			
	SysTick->VAL =0X00;       					  	    
} 

int main()
{
    uint32_t Clock_OK;
    uint8_t i = 0;
    RCC->BDCR |= 1;
    while (!(RCC->BDCR & (1 << 1)));
    RCC->BDCR |= 1 << 8;
    RCC->BDCR |= 1 << 15;
    RCC->CR |= 1 << 16;
    while (!(RCC->CR & (1 << 17)));
    RCC->CFGR |= 4 << 8;
    FLASH->ACR |= 0x2;
    RCC->CFGR |= 1 << 16;
    RCC->CFGR |= 7 << 18;
    RCC->CR |= 1 << 24;
    while (!(RCC->CR & (1 << 25)));
    RCC->CFGR |= 2 << 0;
    do
    {
        Clock_OK = RCC->CFGR & 0x0c;
    } while (Clock_OK != 0x08);

    SysTick->CTRL &= ~(1 << 2);

    RCC->APB2ENR |= 0x0000001c;
    GPIOC->CRH &= 0xff0fffff;
	GPIOC->CRH |= 0x00300000;
    GPIOC->ODR |= 1 << 13;
    GPIOB->CRH &= 0xfffffff0;
	GPIOB->CRH |= 0x00000003;
    GPIOB->ODR |= 1 << 8;
	GPIOA->CRL &= 0xffffff0f;
    GPIOA->CRL |= 0x00000080;
    GPIOA->ODR |= 1 << 1;

	GPIOC->ODR &= ~(1 << 13);
    while (1)
    {
        if (!(GPIOA->IDR & (1 << 1)))
        {
            Delay_ms(100);
            if (!(GPIOA->IDR & (1 << 1)))
            {
                i++;
                i %= 3;
                while (!(GPIOA->IDR & (1 << 1)));
            }
        }

        switch (i)
        {
            case 1:
                GPIOB->ODR &= ~(1 << 8);
                break;
            case 2:
                GPIOB->ODR ^= (1 << 8);
                Delay_ms(500);
                break;
            default:
                GPIOB->ODR |= 1 << 8;
                break;
        }
        
			
    }
}