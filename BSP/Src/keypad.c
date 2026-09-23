#include "keypad.h"
#include "stm32f411xe.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_hal.h"
#include "stm32f4xx.h"
#include <stdint.h>

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

static char raw_scan(Keypad_t *kp){

    // Test column high, others low
    for(uint8_t c=0; c<KEYPAD_COLS;c++){

        for (uint8_t j=0; j<KEYPAD_COLS; j++) {
            if(c==j){
                GPIO_WriteToOutputPin(kp->cols[j].pGPIOx, kp->cols[j].GPIO_PinConfig.GPIO_PinNumber, SET);
            }else{
                GPIO_WriteToOutputPin(kp->cols[j].pGPIOx, kp->cols[j].GPIO_PinConfig.GPIO_PinNumber, RESET);
            }
        }

        // Wait few cycles to output pins to set 
        for(volatile uint8_t d=0; d<20;d++){
            __asm__ volatile("nop"); // DO NOTHING
        }

        for(uint8_t r=0; r<KEYPAD_ROWS; r++){
            uint8_t bit = GPIO_ReadFromInputPin(kp->rows[r].pGPIOx, kp->rows[r].GPIO_PinConfig.GPIO_PinNumber);
            if(bit){
                // DISABLE THE COLUMN
                GPIO_WriteToOutputPin(kp->cols[c].pGPIOx, kp->cols[c].GPIO_PinConfig.GPIO_PinNumber, RESET);
                return KEY_MAP[r][c];
            }
        }
        GPIO_WriteToOutputPin(kp->cols[c].pGPIOx, kp->cols[c].GPIO_PinConfig.GPIO_PinNumber, RESET);

    }
    return '\0';
}

char Keypad_Scan(Keypad_t *kp, uint32_t systick_ms){
    char raw = raw_scan(kp);

    // State machine for debounce
    switch (kp->state) {
    case KEYPAD_STATE_IDLE:
        if(raw != '\0'){
            kp->candidate_key = raw;
            kp->state_enter_tick = systick_ms;                
            kp->state = KEYPAD_STATE_DEBOUNCE;
        }
        break;
    case KEYPAD_STATE_DEBOUNCE:
        if(raw!=kp->candidate_key){ // Debounced, discard the key
            kp->state = KEYPAD_STATE_IDLE;
        }else if((systick_ms - kp->state_enter_tick) >= kp->debounce_ms){
            kp->state = KEYPAD_STATE_PRESSED;
            return kp->candidate_key;
        }
        break;
    case KEYPAD_STATE_PRESSED:
        if(raw == '\0'){ // Key released
            kp->state = KEYPAD_STATE_IDLE;
        }
        break;
    default:
        kp->state = KEYPAD_STATE_IDLE;
        break;
    }

    return '\0';
}