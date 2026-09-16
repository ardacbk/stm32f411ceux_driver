#include <stdint.h>
#include "stm32f411xe.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_hal.h"

// Very primitive delay function
// Just for testing purposes
void delay(void){

    for(volatile uint32_t i=0; i<500000; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed = {0};
    GpioLed.pGPIOx = GPIOC;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&GpioLed);
    while (1)
    {
        GPIO_ToggleOutputPin(GPIOC, 13);
        delay();
    }
}
