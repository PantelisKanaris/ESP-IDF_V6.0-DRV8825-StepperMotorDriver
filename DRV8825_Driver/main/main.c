#include <stdio.h>
#include "DRV8825.h"
#include <driver/pulse_cnt.h>
#include "PCNT.h"
#include "esp_log.h"

static const char *TAG = "MAIN";
void app_main(void)
{
    DRV8825_t * driverStruct = (DRV8825_t *) malloc(sizeof(DRV8825_t));
    // DRV8825_InitializeLedc(driverStruct, 400, 2);
    // pcnt_unit_handle_t * pcnt_unit = NULL;
    // pcnt_unit = PCNT_Initialize(-1000, 1000, 2, -1,PCNT_COUNT_INC, PCNT_PositiveEdgeCounting);
    // PCNT_AddWatchPoint(pcnt_unit, 800);
    // LEDC_PWM_ChangeDutyCycle(&(driverStruct->ledc_struct),8192/2);
    DRV8825_InitializeDriver(driverStruct, 200, 2,13, DRV8825_DIR_CW, -10000, 10000, 2, -1,PCNT_COUNT_INC, PCNT_PositiveEdgeCounting);
    DRV8825_MoveXSteps(driverStruct, 200, 400);
    DRV8825_SetDirection(driverStruct, DRV8825_DIR_CCW);
    vTaskDelay(pdMS_TO_TICKS(10000));
    DRV8825_MoveXSteps(driverStruct, 200, 400);

}
