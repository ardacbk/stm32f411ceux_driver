#include "keypad.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_hal.h"

void Keypad_Init(Keypad_t *kp){
    for(uint8_t r=0; r<KEYPAD_ROWS; r++){
        // Enable RCC Clock
        RCC->AHB1ENR |= (1U << gpio_get_port_code(kp->rows[r].pGPIOx));

        // Configure GPIO Handle
        kp->rows[r].GPIO_PinConfig.GPIO_PinAltFunMode = 0;
        kp->rows[r].GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
        kp->rows[r].GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
        kp->rows[r].GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;
        kp->rows[r].GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

        GPIO_Init(&kp->rows[r]);
    }

    for(uint8_t c=0; c<KEYPAD_COLS; c++){
        RCC->AHB1ENR |= (1U << gpio_get_port_code(kp->cols[c].pGPIOx));

        kp->cols[c].GPIO_PinConfig.GPIO_PinAltFunMode = 0;
        kp->cols[c].GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
        kp->cols[c].GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
        kp->cols[c].GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
        kp->cols[c].GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
        
        GPIO_Init(&kp->cols[c]);

        GPIO_WriteToOutputPin(kp->cols[c].pGPIOx, kp->cols[c].GPIO_PinConfig.GPIO_PinNumber, RESET);
    }
    kp->state = KEYPAD_STATE_IDLE;
    kp->state_enter_tick = 0;
    kp->candidate_key = '\0';
}
