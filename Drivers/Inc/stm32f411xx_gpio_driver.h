#ifndef STM32F411XX_GPIO_DRIVER_H_
#define STM32F411XX_GPIO_DRIVER_H_

#include "stm32f4xx.h"
#include <stdint.h>

typedef struct{
    uint8_t GPIO_PinNumber;         /*possible values @GPIO_PIN_NUMBERS*/
    uint8_t GPIO_PinMode;           /*possible values @GPIO_PIN_MODES*/
    uint8_t GPIO_PinSpeed;          /*possible values @GPIO_PIN_SPEEDS*/
    uint8_t GPIO_PinPuPdControl;    /*possible values @GPIO_PIN_PUPD*/
    uint8_t GPIO_PinOPType;         /*possible values @GPIO_PIN_OP_TYPES*/
    uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;


typedef struct{
    GPIO_TypeDef        *pGPIOx;            // Base Address of GPIO Port
    GPIO_PinConfig_t    GPIO_PinConfig;     // GPIO pin config settings
}GPIO_Handle_t ;


/*
 * @GPIO_PIN_NUMBERS
 * GPIO possible pin numbers
*/
#define GPIO_PIN_NO_0       0
#define GPIO_PIN_NO_1       1
#define GPIO_PIN_NO_2       2
#define GPIO_PIN_NO_3       3
#define GPIO_PIN_NO_4       4
#define GPIO_PIN_NO_5       5
#define GPIO_PIN_NO_6       6
#define GPIO_PIN_NO_7       7
#define GPIO_PIN_NO_8       8
#define GPIO_PIN_NO_9       9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15


/*
 * @GPIO_PIN_MODES
 * GPIO Pin possible modes
*/
#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_ALTFN     2
#define GPIO_MODE_ANALOG    3
#define GPIO_MODE_IT_FT     4 //Falling edge interrupt
#define GPIO_MODE_IT_RT     5 //Rising edge interrupt
#define GPIO_MODE_IT_RFT    6 //Rising falling edge interrupt


/*
 * @GPIO_PIN_OP_TYPES
 * GPIO pin possible output types
*/
#define GPIO_OP_TYPE_PP     0 // Push-pull
#define GPIO_OP_TYPE_OD     1 // Open-drain

/*
 * @GPIO_PIN_SPEEDS
 * GPIO possible output speeds
*/
#define GPIO_SPEED_LOW      0
#define GPIO_SPEED_MEDIUM   1
#define GPIO_SPEED_FAST     2
#define GPIO_SPEED_HIGH     3

/*
 * @GPIO_PIN_PUPD
 * GPIO pin pull-up and pull-down configs
*/
#define GPIO_NO_PUPD        0
#define GPIO_PIN_PU         1
#define GPIO_PIN_PD         2





// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, FunctionalState EnorDi);

// Init and de-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_TypeDef *pGPIOx);


// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);

// Interrupt
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, FunctionalState EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandler(uint8_t PinNumber);


#endif