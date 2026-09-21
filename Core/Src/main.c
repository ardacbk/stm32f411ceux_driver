#include <stdint.h>
#include "stm32f411xe.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_hal.h"
#include "stm32f4xx.h"

// Very primitive delay function
// Just for testing purposes
void delay(void){

    for(volatile uint32_t i=0; i<500000; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed = {0};
    GPIO_Handle_t GpioButton = {0};
    
    GpioLed.pGPIOx = GPIOC;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    


    GpioButton.pGPIOx = GPIOA;
    GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&GpioLed);
    GPIO_Init(&GpioButton);

    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_13, ENABLE);

    uint8_t prev_button_state = 1;
    while (1)
    {
        uint8_t new_button_state = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0);
        if(prev_button_state == 1 && new_button_state == 0){
            GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
        }
        prev_button_state = new_button_state;
    }
}
