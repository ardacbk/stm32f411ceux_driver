#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_hal.h"
#include "stm32f4xx.h"
#include <stdint.h>


// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, FunctionalState EnorDi){
    if(EnorDi == ENABLE){
        if(pGPIOx == GPIOA){
            GPIOA_CLK_EN();
        }
        else if(pGPIOx == GPIOB){
            GPIOB_CLK_EN();
        }
        else if(pGPIOx == GPIOC){
            GPIOC_CLK_EN();
        }
        else if(pGPIOx == GPIOD){
            GPIOD_CLK_EN();
        }
        else if(pGPIOx == GPIOE){
            GPIOE_CLK_EN();
        }
        else if(pGPIOx == GPIOH){
            GPIOH_CLK_EN();
        }
    }
    else{
                if(pGPIOx == GPIOA){
            GPIOA_CLK_DI();
        }
        else if(pGPIOx == GPIOB){
            GPIOB_CLK_DI();
        }
        else if(pGPIOx == GPIOC){
            GPIOC_CLK_DI();
        }
        else if(pGPIOx == GPIOD){
            GPIOD_CLK_DI();
        }
        else if(pGPIOx == GPIOE){
            GPIOE_CLK_DI();
        }
        else if(pGPIOx == GPIOH){
            GPIOH_CLK_DI();
        }
    }


}

// Init and de-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

    uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

    // Configure mode of GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){ 
        pGPIOHandle->pGPIOx->MODER &= ~(0x03U << (2*pin));
        pGPIOHandle->pGPIOx->MODER |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pin));
    }
    else{ // Interrupt mode
        // Will be added later
    }

    // Configure output type register
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x01U << pin);
    pGPIOHandle->pGPIOx->OTYPER |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pin);
    

    // Configure speed of GPIO pin
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x03U << (2*pin));
    pGPIOHandle->pGPIOx->OSPEEDR |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pin));

    // Configure  pull-up/pull down register
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x03U << (2*pin));
    pGPIOHandle->pGPIOx->PUPDR |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2*pin));

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){

        // Avoid if else
        uint8_t afr_idx = pin / 8; // 0: Alternate func low / 1: Alternate func high
        uint8_t afr_pos = pin % 8; // Position of the register
        pGPIOHandle->pGPIOx->AFR[afr_idx] &= ~(0x0FU<< (4* afr_pos)); // Reset with 1111b 
        pGPIOHandle->pGPIOx->AFR[afr_idx] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4* afr_pos));
    }
}

void GPIO_DeInit(GPIO_TypeDef *pGPIOx) {
  if (pGPIOx == GPIOA) {
    GPIOA_REG_RESET();
  } else if (pGPIOx == GPIOB) {
    GPIOB_REG_RESET();
  } else if (pGPIOx == GPIOC) {
    GPIOC_REG_RESET();
  } else if (pGPIOx == GPIOD) {
    GPIOD_REG_RESET();
  } else if (pGPIOx == GPIOE) {
    GPIOE_REG_RESET();
  } else if (pGPIOx == GPIOH) {
    GPIOH_REG_RESET();
  }
}

// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber){
    uint8_t value;
    value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x1U);
    return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx){
    uint16_t value;
    value = (uint16_t) pGPIOx->IDR;
    return value;
}
void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t Value){

    if(Value == SET){
        pGPIOx->ODR |= (1U << PinNumber);
    }
    else {
        pGPIOx->ODR &= ~(1U << PinNumber);
    }

}
void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint16_t Value){
    pGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber){
    pGPIOx->ODR ^= (1U << PinNumber);
}
// Interrupt
// Will be added
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, FunctionalState EnorDi){

}
void GPIO_IRQHandler(uint8_t PinNumber){

}
