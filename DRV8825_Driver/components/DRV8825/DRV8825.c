#include "DRV8825.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void DRV8825_InitializeLedc(DRV8825_t * driverStruct)
{
    LEDC_PWM_InitiliazeLEDC(&(driverStruct->ledc_struct),LEDC_LOW_SPEED_MODE,LEDC_TIMER_0,400,LEDC_TIMER_13_BIT,LEDC_USE_RC_FAST_CLK,LEDC_CHANNEL_0,2);
    LEDC_PWM_ChangeDutyCycle(&(driverStruct->ledc_struct),8192/2);
    vTaskDelay(pdMS_TO_TICKS(5000));
    LEDC_PWM_ChangeDutyCycle(&(driverStruct->ledc_struct),0);
    vTaskDelay(pdMS_TO_TICKS(3000));
    LEDC_PWM_ChangeFrequency(&(driverStruct->ledc_struct),800);
    LEDC_PWM_ChangeDutyCycle(&(driverStruct->ledc_struct),8192/2);
}