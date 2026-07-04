#include <stdio.h>
#include "DRV8825.h"
#include <driver/pulse_cnt.h>
#include "PCNT.h"
#include "esp_log.h"

static const char *TAG = "MAIN";
void app_main(void)
{
    DRV8825_t * driverStruct = (DRV8825_t *) malloc(sizeof(DRV8825_t));
    DRV8825_InitializeLedc(driverStruct);
    pcnt_unit_handle_t * pcnt_unit = NULL;
    pcnt_unit = PCNT_Initialize(-1000, 1000, 2, -1,PCNT_COUNT_INC, PCNT_PositiveEdgeCounting);
    PCNT_AddWatchPoint(pcnt_unit, 800);
    LEDC_PWM_ChangeDutyCycle(&(driverStruct->ledc_struct),8192/2);
    PCNT_Start(pcnt_unit);
    while (1)
    {
        int count = 0;
        ESP_ERROR_CHECK(pcnt_unit_get_count(*pcnt_unit, &count));
        ESP_LOGI(TAG, "PCNT count = %d", count);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
