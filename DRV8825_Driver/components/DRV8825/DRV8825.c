#include "DRV8825.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
static const char *TAG = "DRV8825";
void DRV8825_InitializeLedc(DRV8825_t * driverStruct,int frequencyHz,int gpioOutputPin)
{
    
    LEDC_PWM_InitiliazeLEDC(&(driverStruct->ledc_struct),LEDC_LOW_SPEED_MODE,LEDC_TIMER_0,frequencyHz,LEDC_TIMER_13_BIT,LEDC_USE_RC_FAST_CLK,LEDC_CHANNEL_0,gpioOutputPin);
    LEDC_PWM_ChangeDutyCycle(&(driverStruct->ledc_struct),0);
    driverStruct->current_frequency = frequencyHz;  
}

void DRV8825_InitializeCounter(DRV8825_t * driverStruct,int low_limit, int high_limit, int edge_gpio, int level_gpio,PCNT_CountingMode_enum count_mode,PCNT_EdgeCountingMode_enum edge_count_mode)
{
    driverStruct->event_group = xEventGroupCreate();
    if(driverStruct->event_group == NULL)
    {
        ESP_LOGE(TAG, "ERROR Initializing DRV8825 Counter driverStruct->event_group is NULL");
        return;
    }
    driverStruct->pcnt_unit = PCNT_Initialize(low_limit, high_limit, edge_gpio, level_gpio,count_mode,edge_count_mode, &driverStruct->event_group);
}

void DRV8825_InitializeDriver(DRV8825_t * driverStruct, int frequencyHz,int gpioOutputPin,int low_limit, int high_limit, int edge_gpio, int level_gpio,PCNT_CountingMode_enum count_mode,PCNT_EdgeCountingMode_enum edge_count_mode)
{
    DRV8825_InitializeLedc(driverStruct, frequencyHz, gpioOutputPin);
    ESP_LOGI(TAG, "LEDC Initialized");
    DRV8825_InitializeCounter(driverStruct, low_limit, high_limit, edge_gpio, level_gpio, count_mode, edge_count_mode);
    ESP_LOGI(TAG, "PCNT Initialized");
}

void DRV8825_ClearCounter(DRV8825_t * driverStruct)
{
    PCNT_ClearCount(driverStruct->pcnt_unit);
}

void DRV8825_StartCounter(DRV8825_t * driverStruct)
{
    PCNT_Start(driverStruct->pcnt_unit);
}

void DRV8825_DisableCounter(DRV8825_t * driverStruct)
{
    DRV8825_ClearCounter(driverStruct);
    PCNT_Disable(driverStruct->pcnt_unit);
}

void DRV8825_SetCounterWatchPoint(DRV8825_t * driverStruct, int watch_point)
{
    PCNT_AddWatchPoint(driverStruct->pcnt_unit, watch_point);
}

void DRV8825_MoveXSteps(DRV8825_t * driverStruct, int steps,uint32_t frequencyHz)
{
    //TODO make the steps parameter to correspond to the steps of the stepper motor based on the frequency.
    DRV8825_ClearCounter(driverStruct);
    DRV8825_ChangeFrequency(driverStruct,frequencyHz);
    steps = (frequencyHz*steps);
    DRV8825_SetCounterWatchPoint(driverStruct, steps);
    DRV8825_StartCounter(driverStruct);
    DRV8825_ChangeDutyCycle(driverStruct,8192/2);
    xEventGroupWaitBits(driverStruct->event_group, 0x01, pdTRUE, pdFALSE, portMAX_DELAY);
    DRV8825_ChangeDutyCycle(driverStruct,0);
    DRV8825_ClearCounter(driverStruct);
}

void DRV8825_ChangeDutyCycle(DRV8825_t * driverStruct,uint32_t duty)
{
    LEDC_PWM_ChangeDutyCycle(&(driverStruct->ledc_struct),duty);
}

void DRV8825_ChangeFrequency(DRV8825_t * driverStruct,uint32_t frequencyHz)
{
    LEDC_PWM_ChangeFrequency(&(driverStruct->ledc_struct),frequencyHz);
}

