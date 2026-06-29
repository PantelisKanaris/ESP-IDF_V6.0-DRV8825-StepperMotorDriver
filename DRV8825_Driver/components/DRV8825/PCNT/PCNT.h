#ifndef PCNT_H
#define PCNT_H
#include "driver/pulse_cnt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

typedef enum PCNT_CountingMode_enum
{
    PCNT_COUNT_INC = 0,
    PCNT_COUNT_DEC = 1,
    PCNT_COUNT_MAX
} PCNT_CountingMode_enum;

typedef enum PCNT_EdgeCountingMode_enum
{
    PCNT_PositiveEdgeCounting = 0,
    PCNT_NegativeEdgeCounting = 1,  
}PCNT_EdgeCountingMode_enum;

#endif