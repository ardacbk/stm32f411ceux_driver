#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xe.h"
#include "stm32f411xx_hal.h"
#include "stm32f4xx.h"
#include <stdint.h>


/* ============================================================================
 *                          PERIPHERAL CLOCK CONTROL
 * ============================================================================ */

/**
 * @brief  Enables or disables the peripheral clock for the given GPIO port.
 * @param  pGPIOx: Base address of the GPIO peripheral (GPIOA, GPIOB, etc.)
 * @param  EnorDi: ENABLE or DISABLE
 * @return None
 */
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

/* ============================================================================
 *                          INIT AND DE-INIT FUNCTIONS
 * ============================================================================ */

/**
 * @brief  Initializes the specified GPIO pin according to the specified parameters
 *         (Mode, Output Type, Speed, Pull-Up/Pull-Down, Alternate Function, or EXTI).
 * @param  pGPIOHandle: Pointer to a GPIO_Handle_t structure that contains
 *                      the configuration information for the specified GPIO pin.
 * @return None
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

    uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

    // Configure mode of GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){ 
        pGPIOHandle->pGPIOx->MODER &= ~(0x03U << (2*pin));
        pGPIOHandle->pGPIOx->MODER |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pin));
    }
    else{ // Interrupt mode
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
            EXTI->FTSR |= (0X1U << pin);
            EXTI->RTSR &= ~(0X1U << pin); // Clear the rising edge register
        } else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
            EXTI->RTSR |= (0X1U << pin);
            EXTI->FTSR &= ~(0X1U << pin); // Clear the falling edge register
        }else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT) {
            EXTI->RTSR |= (0X1U << pin);
            EXTI->FTSR |= (0X1U << pin);        
        }
        SYSCFG_CLK_EN();
        uint8_t port_code = gpio_get_port_code(pGPIOHandle->pGPIOx); 
        uint8_t exticr_idx = pin / 4;
        uint8_t exticr_pos = pin % 4;

        //Set GPIO pin to input
        pGPIOHandle->pGPIOx->MODER &= ~(0x3U << (pin * 2));

        EXTI->IMR |= (0x1U << pin); // Remove the bit mask
        SYSCFG->EXTICR[exticr_idx] &= ~(0xFU << (exticr_pos * 4)); // Clear the EXTICR bit
        SYSCFG->EXTICR[exticr_idx] |= (port_code << (exticr_pos * 4)); // set the EXTICR bit
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

/**
 * @brief  Resets all registers of the given GPIO port to their default reset states.
 * @param  pGPIOx: Base address of the GPIO peripheral (GPIOA, GPIOB, etc.)
 * @return None
 */
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

/* ============================================================================
 *                          DATA READ AND WRITE APIS
 * ============================================================================ */

/**
 * @brief  Reads the input state of a specific pin on the given GPIO port.
 * @param  pGPIOx: Base address of the GPIO peripheral
 * @param  PinNumber: Pin number to read (0 to 15)
 * @return 0 or 1 (logic state of the pin)
 */
uint8_t GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber){
    uint8_t value;
    value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x1U);
    return value;
}

/**
 * @brief  Reads the input states of all 16 pins of the given GPIO port.
 * @param  pGPIOx: Base address of the GPIO peripheral
 * @return 16-bit value representing the port's input data register (IDR)
 */
uint16_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx){
    uint16_t value;
    value = (uint16_t) pGPIOx->IDR;
    return value;
}

/**
 * @brief  Sets or clears the output logic level of a specific GPIO pin.
 * @param  pGPIOx: Base address of the GPIO peripheral
 * @param  PinNumber: Pin number to write (0 to 15)
 * @param  Value: SET (1) or RESET (0)
 * @return None
 */
void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t Value){

    if(Value == SET){
        pGPIOx->ODR |= (1U << PinNumber);
    }
    else {
        pGPIOx->ODR &= ~(1U << PinNumber);
    }

}

/**
 * @brief  Writes a 16-bit value directly to the entire GPIO port output data register.
 * @param  pGPIOx: Base address of the GPIO peripheral
 * @param  Value: 16-bit value to write to the ODR register
 * @return None
 */
void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint16_t Value){
    pGPIOx->ODR = Value;
}

/**
 * @brief  Toggles the current output state of the specified GPIO pin.
 * @param  pGPIOx: Base address of the GPIO peripheral
 * @param  PinNumber: Pin number to toggle (0 to 15)
 * @return None
 */
void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber){
    pGPIOx->ODR ^= (1U << PinNumber);
}

/* ============================================================================
 *                          INTERRUPT CONFIGURATION & HANDLING
 * ============================================================================ */

/**
 * @brief  Enables or disables a specific IRQ in the ARM Cortex-M NVIC controller.
 * @param  IRQNumber: IRQ number / position (e.g. EXTI0_IRQn, EXTI1_IRQn, ...)
 * @param  EnorDi: ENABLE or DISABLE
 * @return None
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, FunctionalState EnorDi){
    if(EnorDi == ENABLE){
        NVIC_EnableIRQ((IRQn_Type) IRQNumber);
    }
    else{
        NVIC_DisableIRQ((IRQn_Type)IRQNumber);
    }
}

/**
 * @brief  Configures the priority level of a specific IRQ in the NVIC controller.
 * @param  IRQNumber: IRQ number / position (e.g. EXTI0_IRQn, EXTI1_IRQn, ...)
 * @param  IRQPriority: Priority value (0 to 15 for STM32F411, where 0 is highest)
 * @return None
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority){
    NVIC_SetPriority((IRQn_Type)IRQNumber, (uint32_t)IRQPriority);
}

/**
 * @brief  GPIO EXTI Interrupt Service Routine (ISR) helper.
 *         Checks and clears the pending bit in EXTI_PR for the specified pin.
 * @param  PinNumber: Pin number associated with the EXTI line (0 to 15)
 * @note   Writing '1' to EXTI->PR clears the pending bit (rc_w1 behavior).
 *         Direct assignment (=) is intentionally used instead of (|=) to avoid race conditions.
 * @return None
 */
void GPIO_IRQHandler(uint8_t PinNumber){
    if(EXTI->PR & (0x1U << PinNumber)){
        EXTI->PR = (0x1U << PinNumber); // Dont use |= to prevent race condition
    }
}
