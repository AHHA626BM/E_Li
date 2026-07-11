#include "stm32f10x.h"

int main()
{
    unsigned int Clock_OK;
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

    RCC->APB2ENR |= 0x0000001c;
    GPIOC->CRH &= 0xff0fffff;
	GPIOC->CRH |= 0x00300000;
    GPIOB->CRH &= 0xfffffff0;
	GPIOB->CRH |= 0x00000003;
	GPIOA->CRL &= 0xffffff0f;
    GPIOA->CRL |= 0x00000080;
    GPIOA->ODR |= 1 << 1;

	GPIOC->ODR &= ~(1 << 13);
    while (1)
    {
			
    }
}