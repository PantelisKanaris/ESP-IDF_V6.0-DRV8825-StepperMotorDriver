#include "LEDC_PWM.h"
#include "esp_log.h"
#include "driver/ledc.h"

const char *TAG = "LEDC";

void LEDC_PWM_InitializeTimer(LedcPwm_s *ledcPwmStruct, ledc_mode_t speedMode, ledc_timer_t timerNumber, uint32_t frequencyHz, ledc_timer_bit_t resolutionPwm, ledc_clk_cfg_t sourceClock)
{
    
    if (ledcPwmStruct == NULL || frequencyHz == 0)
    {
        ESP_LOGE(TAG, "ERROR Initializing LEDC TIMER some parameter is null or negative");
        return ;
    }
    ledc_timer_config_t *ledcTimerConfigurationStruct = (ledc_timer_config_t *)calloc(1,sizeof(ledc_timer_config_t));
    if (ledcTimerConfigurationStruct == NULL)
    {
        ESP_LOGE(TAG, "ERROR Initializing LEDC TIMER ledctimer struct not initialized correctly");
        return ;
    }
    ledcTimerConfigurationStruct->speed_mode = speedMode;
    ledcTimerConfigurationStruct->duty_resolution = resolutionPwm;
    ledcTimerConfigurationStruct->timer_num = timerNumber;
    ledcTimerConfigurationStruct->freq_hz = frequencyHz;
    ledcTimerConfigurationStruct->clk_cfg = sourceClock;
    ESP_LOGI(TAG,"Before Initialization");
    ESP_ERROR_CHECK(ledc_timer_config(ledcTimerConfigurationStruct));
    ledcPwmStruct->ledcTimerConfigurationStruct = ledcTimerConfigurationStruct;
    ESP_LOGI(TAG, "LEDC TIMER initialized successfully");
}

void LEDC_PWM_InitializeChannel(LedcPwm_s *ledcPwmStruct, ledc_mode_t speedMode, ledc_channel_t channel, ledc_timer_t timer, uint8_t gpio)
{
    ledc_channel_config_t *ledcChannelConfigurationStruct = (ledc_channel_config_t *)calloc(1,sizeof(ledc_channel_config_t));
    if (ledcChannelConfigurationStruct == NULL)
    {
        ESP_LOGE(TAG, "ERROR Initializing LEDC Channel struct not initialized correctly");
        return ;
    }
    ledcChannelConfigurationStruct->channel = channel;
    ledcChannelConfigurationStruct->speed_mode = speedMode;
    ledcChannelConfigurationStruct->timer_sel = timer;
    ledcChannelConfigurationStruct->gpio_num = gpio;
    ledcChannelConfigurationStruct->duty = 0;
    ledcChannelConfigurationStruct->hpoint = 0;
    ESP_ERROR_CHECK(ledc_channel_config(ledcChannelConfigurationStruct));
    ledcPwmStruct->ledcChannelConfigurationStruct = ledcChannelConfigurationStruct;
    ESP_LOGI(TAG, "LEDC Channel initialized successfully");
}

void LEDC_PWM_ChangeDutyCycle(LedcPwm_s *ledcPwmStruct, uint32_t duty)
{
    ledc_mode_t speedmode = ledcPwmStruct->ledcTimerConfigurationStruct->speed_mode;
    ledc_channel_t channel = ledcPwmStruct->ledcChannelConfigurationStruct->channel;
    ESP_ERROR_CHECK(ledc_set_duty(speedmode, channel, duty));
    ESP_ERROR_CHECK(ledc_update_duty(speedmode, channel));
    uint32_t currentDuty = ledc_get_duty(speedmode, channel);
    if (currentDuty != duty)
    {
        ESP_LOGE(TAG, "Failed to change Duty Cycle");
    }
}

void LEDC_PWM_ChangeFrequency(LedcPwm_s *ledcPwmStruct, uint32_t freq_hz)
{
    ledc_mode_t speedmode = ledcPwmStruct->ledcTimerConfigurationStruct->speed_mode;
    ledc_timer_t timer = ledcPwmStruct->ledcTimerConfigurationStruct->timer_num;
    ESP_ERROR_CHECK(ledc_set_freq(speedmode, timer, freq_hz));
    uint32_t currentFreq = ledc_get_freq(speedmode, timer);
    if (currentFreq != freq_hz)
    {
        ESP_LOGE(TAG, "Failed to change Frequency");
    }
}


void LEDC_PWM_InitiliazeLEDC(LedcPwm_s *ledcPwmStruct ,ledc_mode_t speedMode, ledc_timer_t timerNumber, uint32_t frequencyHz, 
                                ledc_timer_bit_t resolutionPwm, ledc_clk_cfg_t sourceClock,ledc_channel_t channel,uint8_t gpio)
{
    LEDC_PWM_InitializeTimer(ledcPwmStruct,speedMode,timerNumber,frequencyHz,resolutionPwm,sourceClock);
    LEDC_PWM_InitializeChannel(ledcPwmStruct,speedMode,channel,timerNumber,gpio);
}