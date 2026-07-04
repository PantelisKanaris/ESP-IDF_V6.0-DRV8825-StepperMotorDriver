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

pcnt_unit_handle_t * PCNT_Initialize(int low_limit, int high_limit, int edge_gpio, int level_gpio,PCNT_CountingMode_enum count_mode,PCNT_EdgeCountingMode_enum edge_count_mode, EventGroupHandle_t * event_group);
void PCNT_ClearCount(pcnt_unit_handle_t* pcnt_unit);
void PCNT_Disable(pcnt_unit_handle_t* pcnt_unit);
void PCNT_Start(pcnt_unit_handle_t* pcnt_unit);
void PCNT_Enable(pcnt_unit_handle_t* pcnt_unit);
int PCNT_AddWatchPoint(pcnt_unit_handle_t* pcnt_unit, int watch_point);

#endif