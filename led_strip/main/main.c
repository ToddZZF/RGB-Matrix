#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_strip.h"

#define RGB_PIN 3

static const char *TAG = "ws2812";
static uint8_t s_led_state = 0;
static led_strip_t *pStrip;

static void blink_led(void)
{
    if (s_led_state)
    {
        pStrip->set_pixel(pStrip, 0,1,0,0);
        pStrip->set_pixel(pStrip, 1,0,1,0);
        pStrip->set_pixel(pStrip, 2,0,0,1);
        pStrip->refresh(pStrip, 100);
    } else {
        pStrip->clear(pStrip, 50);
    }
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Config WS2812");
    pStrip=led_strip_init(0, RGB_PIN, 3);
    pStrip->clear(pStrip, 50);
}

void app_main(void)
{
    configure_led();

    for(;;) {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        blink_led();
        s_led_state = !s_led_state;
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}