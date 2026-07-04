#ifndef DRV8825_H
#define DRV8825_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LEDC_PWM/LEDC_PWM.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "PCNT/PCNT.h"

typedef enum {
    DRV8825_STEP_MODE_FULL = 0,
    DRV8825_STEP_MODE_HALF = 1,
    DRV8825_STEP_MODE_QUARTER = 2,
    DRV8825_STEP_MODE_EIGHTH = 3,
    DRV8825_STEP_MODE_SIXTEENTH = 4,
    DRV8825_STEP_MODE_THIRTY_SECOND = 5
} StepMode_e;

typedef enum {
    DRV8825_DIR_CW = 1,
    DRV8825_DIR_CCW = 0
} Direction_e;

typedef struct{
    StepMode_e step_mode;
    LedcPwm_s ledc_struct;
    pcnt_unit_handle_t * pcnt_unit;
    EventGroupHandle_t event_group;
    Direction_e direction;
    uint8_t dir_pin;
    uint8_t step_pin;
    uint8_t enable_pin;
    uint8_t sleep_pin;
    uint8_t reset_pin;
    uint8_t fault_pin;
    uint8_t ms0_pin;
    uint8_t ms1_pin;
    uint8_t ms2_pin;
    int current_frequency;
}DRV8825_t;

void DRV8825_InitializeLedc(DRV8825_t * driverStruct,int frequencyHz,int gpioOutputPin);
void DRV8825_InitializeCounter(DRV8825_t * driverStruct,int low_limit, int high_limit, int edge_gpio, int level_gpio,PCNT_CountingMode_enum count_mode,PCNT_EdgeCountingMode_enum edge_count_mode);
void DRV8825_InitializeDriver(DRV8825_t * driverStruct, int frequencyHz,int gpioOutputPin,int dirpin,Direction_e direction,int low_limit, int high_limit, int edge_gpio, int level_gpio,PCNT_CountingMode_enum count_mode,PCNT_EdgeCountingMode_enum edge_count_mode);
void DRV8825_ChangeDutyCycle(DRV8825_t * driverStruct,uint32_t duty);
void DRV8825_ClearCounter(DRV8825_t * driverStruct);
void DRV8825_StartCounter(DRV8825_t * driverStruct);
void DRV8825_DisableCounter(DRV8825_t * driverStruct);
void DRV8825_SetCounterWatchPoint(DRV8825_t * driverStruct, int watch_point);
void DRV8825_MoveXSteps(DRV8825_t * driverStruct, int steps,uint32_t frequencyHz);
void DRV8825_ChangeFrequency(DRV8825_t * driverStruct,uint32_t frequencyHz);
void DRV8825_SetDirection(DRV8825_t *driverStruct, Direction_e direction);
#endif