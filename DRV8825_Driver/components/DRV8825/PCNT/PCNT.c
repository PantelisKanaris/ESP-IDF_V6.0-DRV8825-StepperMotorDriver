#include "PCNT.h"
#include "esp_log.h"

const char *TAG = "PCNT";
pcnt_unit_handle_t * PCNT_InitializeUnit(int low_limit , int high_limit)
{
    if(low_limit >= high_limit)
    {
        ESP_LOGE(TAG, "ERROR Initializing PCNT unit low limit is greater than or equal to high limit");
        return NULL;
    }
    pcnt_unit_config_t * unit_config = (pcnt_unit_config_t *)calloc(1, sizeof(pcnt_unit_config_t));
    unit_config->high_limit = high_limit;
    unit_config->low_limit = low_limit;
    unit_config->clk_src = PCNT_CLK_SRC_DEFAULT;
    pcnt_unit_handle_t pcnt_unit = NULL;
    ESP_ERROR_CHECK(pcnt_new_unit(unit_config, &pcnt_unit));
    ESP_LOGI(TAG, "PCNT unit initialized successfully");
    return pcnt_unit;
}

pcnt_channel_handle_t * PCNT_InitializeChannel(pcnt_unit_handle_t pcnt_unit, int edge_gpio, int level_gpio)
{
    pcnt_chan_config_t * channel_config = (pcnt_chan_config_t *)calloc(1, sizeof(pcnt_chan_config_t));
    channel_config->edge_gpio_num = edge_gpio;
    channel_config->level_gpio_num = level_gpio;
    pcnt_channel_handle_t pcnt_chan = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, channel_config, &pcnt_chan));
    ESP_LOGI(TAG, "PCNT channel initialized successfully");
    return pcnt_chan;
}

int PCNT_SetEdgeCountingMode(pcnt_channel_handle_t* pcnt_chan,PCNT_CountingMode_enum count_mode,PCNT_EdgeCountingMode_enum edge_count_mode)
{

    if(count_mode == PCNT_COUNT_INC && edge_count_mode == PCNT_PositiveEdgeCounting)
    {
        ESP_ERROR_CHECK(pcnt_channel_set_edge_action(*pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_HOLD));
    }
    else if(count_mode == PCNT_COUNT_DEC && edge_count_mode == PCNT_PositiveEdgeCounting)
    {
        ESP_ERROR_CHECK(pcnt_channel_set_edge_action(*pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_HOLD));
    }
    else if(count_mode == PCNT_COUNT_INC && edge_count_mode == PCNT_NegativeEdgeCounting)
    {
        ESP_ERROR_CHECK(pcnt_channel_set_edge_action(*pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_HOLD, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    }
    else if(count_mode == PCNT_COUNT_DEC && edge_count_mode == PCNT_NegativeEdgeCounting)
    {
        ESP_ERROR_CHECK(pcnt_channel_set_edge_action(*pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_HOLD, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    }
    else
    {
        ESP_LOGE(TAG, "ERROR Setting Edge Counting Mode invalid parameters");
        return 0;
    }
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(*pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_LOGI(TAG, "PCNT counting mode set successfully");
    return 1;
}

int PCNT_PCNTAddWatchPoint(pcnt_unit_handle_t* pcnt_unit, int watch_point)
{
    ESP_ERROR_CHECK(pcnt_unit_add_watch_point(*pcnt_unit, watch_point));
    ESP_ERROR_CHECK(pcnt_unit_clear_count(*pcnt_unit));
    ESP_LOGI(TAG, "PCNT watch point added successfully");
    return 1;
}

//this should be called in the ISR so we dont have any delays you need to enable it from the kconfig see documentation for more details
static void PCNT_event_handler(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *event_data, void *user_data)
{
    pcnt_watch_event_data_t *watch_event_data = (pcnt_watch_event_data_t *)event_data;
    //here we should trigger the eventgroup event to notify the application that the watch point has been reached
    ESP_LOGI(TAG, "PCNT watch point reached: %d", watch_event_data->watch_point_value);
}

void PCNT_RegisterEventHandler(pcnt_unit_handle_t* pcnt_unit)
{
    pcnt_event_callbacks_t cbs = {.on_reach = PCNT_event_handler};
    ESP_ERROR_CHECK(pcnt_unit_register_event_callbacks(*pcnt_unit, &cbs, NULL));
    ESP_LOGI(TAG, "PCNT event handler registered successfully");
}

void PCNT_Enable(pcnt_unit_handle_t* pcnt_unit)
{
    ESP_ERROR_CHECK(pcnt_unit_enable(*pcnt_unit));
    ESP_LOGI(TAG, "PCNT enabled successfully");
}

void PCNT_Start(pcnt_unit_handle_t* pcnt_unit)
{
    ESP_ERROR_CHECK(pcnt_unit_start(*pcnt_unit));
    ESP_LOGI(TAG, "PCNT started successfully");
}

void PCNT_ClearCount(pcnt_unit_handle_t* pcnt_unit)
{
    ESP_ERROR_CHECK(pcnt_unit_stop(*pcnt_unit));
    ESP_ERROR_CHECK(pcnt_unit_clear_count(*pcnt_unit));
    ESP_LOGI(TAG, "PCNT count cleared successfully");
}

void PCNT_Disable(pcnt_unit_handle_t* pcnt_unit)
{
    ESP_ERROR_CHECK(pcnt_unit_disable(*pcnt_unit));
    ESP_LOGI(TAG, "PCNT disabled successfully");
}   