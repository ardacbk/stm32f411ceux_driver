#include <stdint.h>
#include "stm32f411xe.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_hal.h"
#include "stm32f411xx_systick_driver.h"
#include "stm32f4xx.h"
#include "keypad.h"
#include "system_stm32f4xx.h"



int main(void)
{

    SysTick_Init(SystemCoreClock);
    
    
    
    // Row1 = PB10 // Row2 = PB12 // Row3 = PB13 // Row4 = PB14
    // Col1 = PA1  // Col2 = PA2  // Col3 = PA3  // Col4 = PA4
    Keypad_t kp = {
        .rows = {
            {.pGPIOx = GPIOB, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_10} },   //PB10
            {.pGPIOx = GPIOB, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_12} },   //PB12
            {.pGPIOx = GPIOB, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_13} },   //PB13
            {.pGPIOx = GPIOB, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_14} },   //PB14
        },
        .cols = {
        {.pGPIOx = GPIOA, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_1} },    //PA1
        {.pGPIOx = GPIOA, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_2} },    //PA2
        {.pGPIOx = GPIOA, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_3} },    //PA3
        {.pGPIOx = GPIOA, .GPIO_PinConfig = {.GPIO_PinNumber = GPIO_PIN_NO_4} },    //PA4

        },
        .debounce_ms = 20
    };

    Keypad_Init(&kp);
    while(1){
        char key = Keypad_Scan(&kp, SysTick_Get_Ms());
        if(key != '\0'){
            char found = key; // Added for debugging
        }
    }
}
