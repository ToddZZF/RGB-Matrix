# driver

目前底层使用 RMT 驱动 LED，但根据 [FastLED-idf](https://github.com/bbulkow/FastLED-idf) README 中所说的，I2S 比 RMT 更好，所以未来可能会迁移到 I2S。

至于 I2C 和直接操作 GPIO，前者的资源开销和速度都太慢了（见 [ESP32: FastLED vs. NeoPixelBus vs. NeoPixel Library](https://blog.ja-ke.tech/2019/06/02/neopixel-performance.html)），后者不适合用于 RTOS 中。

## API

```c
struct ws2812_s
    {
        esp_err_t (*set_pixel)(ws2812_t *ws2812, uint32_t index, uint32_t red, uint32_t green, uint32_t blue);
        esp_err_t (*refresh)(ws2812_t *ws2812, uint32_t timeout_ms);
        esp_err_t (*clear)(ws2812_t *ws2812, uint32_t timeout_ms);
        esp_err_t (*ws2812_reset)(ws2812_t *ws2812, uint32_t timeout_ms);       
        esp_err_t (*del)(ws2812_t *ws2812);

        rmt_channel_t rmt_channel;
        uint32_t strip_len;
        uint8_t buffer[0];
    } ws2812_t;

ws2812_t *ws2812_init(uint8_t channel, uint8_t gpio, uint16_t led_num);

esp_err_t ws2812_denit(ws2812_t *ws2812);
```

用法：

```c
static ws2812_t *ws2812; //ws2812 device

ws2812 = ws2812_init(0, RGB_PIN, 3); // init

ws2812->set_pixel(ws2812, 0, 1, 0, 0); // set pixel (safe)
// or
ws2812->buffer[0 * 3 + 1] = 1; // set pixel (unsafe)

ws2812->refresh(ws2812, 100); // refresh

ws2812->clear(ws2812, 50); //clear all pixels

ws2812_denit(ws2812); //denit 
```
