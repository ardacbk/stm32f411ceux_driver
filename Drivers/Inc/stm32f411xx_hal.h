#ifndef STM32F411XX_H_
#define STM32F411XX_H_

#include "stm32f4xx.h"

/* ===================== ENABLE MACROS ================*/
 
// GPIOx Clock Enable Macros
#define GPIOA_CLK_EN() ( RCC->AHB1ENR |= (1U << 0))
#define GPIOB_CLK_EN() ( RCC->AHB1ENR |= (1U << 1))
#define GPIOC_CLK_EN() ( RCC->AHB1ENR |= (1U << 2))
#define GPIOD_CLK_EN() ( RCC->AHB1ENR |= (1U << 3))
#define GPIOE_CLK_EN() ( RCC->AHB1ENR |= (1U << 4))
#define GPIOH_CLK_EN() ( RCC->AHB1ENR |= (1U << 7))

// I2Cx Clock Enable Macros
#define I2C1_CLK_EN() (RCC->APB1ENR |= (1U << 21))
#define I2C2_CLK_EN() (RCC->APB1ENR |= (1U << 22))
#define I2C3_CLK_EN() (RCC->APB1ENR |= (1U << 23))


// SPIx Clock Enable Macros
#define SPI1_CLK_EN() (RCC->APB2ENR |= (1U << 12))
#define SPI2_CLK_EN() (RCC->APB1ENR |= (1U << 14))
#define SPI3_CLK_EN() (RCC->APB1ENR |= (1U << 15))
#define SPI4_CLK_EN() (RCC->APB2ENR |= (1U << 13))
#define SPI5_CLK_EN() (RCC->APB2ENR |= (1U << 20))

// USARTx Clock Enable Macros
#define USART1_CLK_EN() (RCC->APB2ENR |= (1U << 4))
#define USART2_CLK_EN() (RCC->APB1ENR |= (1U << 17))
#define USART6_CLK_EN() (RCC->APB2ENR |= (1U << 5))

// SYSCFG Clock Enable Macro
#define SYSCFG_CLK_EN() (RCC->APB2ENR |= (1U << 14))


/* ===================== DISABLE MACROS ================*/

// GPIOx Clock Disable Macros
#define GPIOA_CLK_DI() ( RCC->AHB1ENR &= ~(1U << 0))
#define GPIOB_CLK_DI() ( RCC->AHB1ENR &= ~(1U << 1))
#define GPIOC_CLK_DI() ( RCC->AHB1ENR &= ~(1U << 2))
#define GPIOD_CLK_DI() ( RCC->AHB1ENR &= ~(1U << 3))
#define GPIOE_CLK_DI() ( RCC->AHB1ENR &= ~(1U << 4))
#define GPIOH_CLK_DI() ( RCC->AHB1ENR &= ~(1U << 7))

// I2Cx Clock Disable Macros
#define I2C1_CLK_DI() (RCC->APB1ENR &= ~(1U << 21))
#define I2C2_CLK_DI() (RCC->APB1ENR &= ~(1U << 22))
#define I2C3_CLK_DI() (RCC->APB1ENR &= ~(1U << 23))


// SPIx Clock Disable Macros
#define SPI1_CLK_DI() (RCC->APB2ENR &= ~(1U << 12))
#define SPI2_CLK_DI() (RCC->APB1ENR &= ~(1U << 14))
#define SPI3_CLK_DI() (RCC->APB1ENR &= ~(1U << 15))
#define SPI4_CLK_DI() (RCC->APB2ENR &= ~(1U << 13))
#define SPI5_CLK_DI() (RCC->APB2ENR &= ~(1U << 20))

// USARTx Clock Disable Macros
#define USART1_CLK_DI() (RCC->APB2ENR &= ~(1U << 4))
#define USART2_CLK_DI() (RCC->APB1ENR &= ~(1U << 17))
#define USART6_CLK_DI() (RCC->APB2ENR &= ~(1U << 5))

// SYSCFG Clock Disable Macro
#define SYSCFG_CLK_DI() (RCC->APB2ENR &= ~(1U << 14))



#endif /* STM32F411XX_H_ */
