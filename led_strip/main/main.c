#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ws2812.h"
#include "color.h"
#include "fast_hsv2rgb.h"

#define RGB_PIN 3

static const char *TAG = "ws2812";
static uint8_t s_led_state = 0;
static ws2812_t *ws2812;

static void blink_led(void)
{
    static uint8_t r,g,b;
    static uint16_t h;
    static uint8_t s,v;
    if (s_led_state)
    {
        ws2812->set_pixel(ws2812, 0, r, g, b);
        ws2812->refresh(ws2812, 100);
    }
    else
    {
        h=(h+10)%1536;
        s=255;
        v=13;
        // hsv2rgb(h,s,v,&r,&g,&b);
        // ESP_LOGI(TAG, "H:%i S:%i, V:%i", h,s,v);
        // ESP_LOGI(TAG, "slow R:%i G:%i, B:%i", r,g,b);
        fast_hsv2rgb_32bit(h,s,v,&r,&g,&b);
        ESP_LOGI(TAG, "fast R:%i G:%i, B:%i", r,g,b);
    }
}

static void blink_led_2(void)
{
    if (s_led_state)
    {
        ws2812->buffer[0 * 3 + 0] = 1 & 0xFF;
        ws2812->buffer[1 * 3 + 1] = 1 & 0xFF;
        ws2812->buffer[2 * 3 + 2] = 1 & 0xFF;
        ws2812->refresh(ws2812, 1);
        ws2812->refresh(ws2812, 1);
        ws2812->refresh(ws2812, 1);
    }
    else
    {
        ws2812->clear(ws2812, 50);
    }
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Config WS2812");
    ws2812 = ws2812_init(0, RGB_PIN, 3);
    ws2812->clear(ws2812, 50);
}

void app_main(void)
{
    configure_led();

    for (;;)
    {
        //ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        blink_led();
        s_led_state = !s_led_state;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}