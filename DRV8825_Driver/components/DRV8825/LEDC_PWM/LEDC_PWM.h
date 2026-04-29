#ifndef LEDC_PWM_H
#define LEDC_PWM_H
#include <stdint.h>
#include <stdio.h>
#include "hal/ledc_types.h"
#include "driver/ledc.h"

typedef struct LedcPwm_s
{
    ledc_timer_config_t *ledcTimerConfigurationStruct; 
    ledc_channel_config_t * ledcChannelConfigurationStruct;
}LedcPwm_s;


void LEDC_PWM_InitiliazeLEDC(LedcPwm_s *ledcPwmStruct ,ledc_mode_t speedMode, ledc_timer_t timerNumber, uint32_t frequencyHz, 
                                ledc_timer_bit_t resolutionPwm, ledc_clk_cfg_t sourceClock,ledc_channel_t channel,uint8_t gpio);



void LEDC_PWM_ChangeFrequency(LedcPwm_s *ledcPwmStruct, uint32_t freq_hz);

void LEDC_PWM_ChangeDutyCycle(LedcPwm_s *ledcPwmStruct, uint32_t duty);

                                
#endif