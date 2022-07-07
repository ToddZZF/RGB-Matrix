#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_strip.h"

#define RGB_PIN 3

static const char *TAG = "ws2812";
static uint8_t s_led_state = 0;
static ws2812_t *ws2812;

static void blink_led(void)
{
    if (s_led_state)
    {
        ws2812->set_pixel(ws2812, 0, 1, 0, 0);
        ws2812->set_pixel(ws2812, 1, 0, 1, 0);
        ws2812->set_pixel(ws2812, 2, 0, 0, 1);
        ws2812->refresh(ws2812, 100);
    }
    else
    {
        ws2812->clear(ws2812, 50);
    }
}

static void blink_led_2(void)
{
    if (s_led_state)
    {
        ws2812->buffer[0 * 3 + 0] = 1 & 0xFF;
        ws2812->buffer[1 * 3 + 1] = 1 & 0xFF;
        ws2812->buffer[2 * 3 + 2] = 1 & 0xFF;
        ws2812->refresh(ws2812, 100);
    }
    else
    {
        ws2812->clear(ws2812, 50);
    }
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Config WS2812");
    ws2812 = led_strip_init(0, RGB_PIN, 3);
    ws2812->clear(ws2812, 50);
}

void app_main(void)
{
    configure_led();

    for (;;)
    {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        blink_led_2();
        s_led_state = !s_led_state;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}