#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f411xe.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_hal.h"
#include <stdint.h>


#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

static const char KEY_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'},
};

typedef enum{
    KEYPAD_STATE_IDLE=0,
    KEYPAD_STATE_DEBOUNCE,
    KEYPAD_STATE_PRESSED
} Keypad_State_t;

typedef struct{
    GPIO_Handle_t    rows[KEYPAD_ROWS];
    GPIO_Handle_t    cols[KEYPAD_COLS];
    uint32_t        debounce_ms;

    Keypad_State_t  state;
    uint32_t        state_enter_tick;
    char            candidate_key;
} Keypad_t;


void Keypad_Init(Keypad_t *kp);

char Keypad_Scan(Keypad_t *kp, uint32_t systick_ms);

#endif // KEYPAD_H_