#ifndef STM32F411XX_SYSTICK_DRIVER_H_
#define STM32F411XX_SYSTICK_DRIVER_H_

#include <stdint.h>


void SysTick_Init(uint32_t core_clock_hz);

uint32_t SysTick_Get_Ms(void);


#endif  // STM32F411XX_SYSTICK_DRIVER_H_