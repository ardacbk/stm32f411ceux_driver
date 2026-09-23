#include "stm32f411xx_systick_driver.h"
#include "stm32f411xe.h"
#include <stdint.h>

/*
 *   CTRL  - control/status: enable bit, interrupt-enable bit,
 *           clock source bit, and a "did it count down to 0 since
 *           last read" flag (bit 16, unused here).
 *   LOAD  - the value VAL reloads to when it hits 0. This is what
 *           sets the period.
 *   VAL   - the current counter value. Writing any value to it
 *           resets it to 0 (that's a quirk of this register).
 */

#define SYSTICK_CTRL_ENABLE     (1U << 0)
#define SYSTICK_CTRL_TICKINT    (1U << 1)
#define SYSTICK_CTRL_CLKSOURCE  (1U << 2)

static volatile uint32_t g_systick_ms = 0;

void SysTick_Init(uint32_t core_clock_hz){
    uint32_t reload_val = (core_clock_hz / 1000UL) - 1UL; // -1 because systick counts 0 too 

    SysTick->CTRL = 0;          
    SysTick->LOAD = reload_val;
    SysTick->VAL = 0;

    SysTick->CTRL = SYSTICK_CTRL_CLKSOURCE|SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT;
}

void SysTick_Handler(void){
    g_systick_ms++;
}

uint32_t SysTick_Get_Ms(void){
    return g_systick_ms;
}
