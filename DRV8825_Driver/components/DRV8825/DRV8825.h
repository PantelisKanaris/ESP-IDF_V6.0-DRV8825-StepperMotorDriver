#ifndef DRV8825_H
#define DRV8825_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum {
    DRV8825_STEP_MODE_FULL = 0,
    DRV8825_STEP_MODE_HALF = 1,
    DRV8825_STEP_MODE_QUARTER = 2,
    DRV8825_STEP_MODE_EIGHTH = 3,
    DRV8825_STEP_MODE_SIXTEENTH = 4,
    DRV8825_STEP_MODE_THIRTY_SECOND = 5
} StepMode_e;

typedef enum {
    DRV8825_DIR_CW = 0,
    DRV8825_DIR_CCW = 1
} Direction_e;

typedef struct{
    StepMode_e step_mode;
    Direction_e direction;
    uint8_t step_pin;
    uint8_t enable_pin;
    uint8_t sleep_pin;
    uint8_t reset_pin;
    uint8_t fault_pin;
    uint8_t ms0_pin;
    uint8_t ms1_pin;
    uint8_t ms2_pin;
}DRV8825_t;


#endif