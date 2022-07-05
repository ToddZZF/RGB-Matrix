# led_strip

演示如何利用官方的 led_strip 来驱动 WS2812 灯带。要使用该库，需要在项目根目录下的 `CMakeList.txt` 文件中添加：

```c
set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/led_strip)
```

或建立一个 components，并将 `$ENV{IDF_PATH}/examples/common_components/led_strip` 中的 `.h`、`.c` 文件复制进去。

## API 解释

led_strip 库利用了 [Remote Control Transceiver (RMT)](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32c3/api-reference/peripherals/rmt.html)，也就是红外遥控收发器。

该库定义了 `led_strip_config_t` 结构体用于存储最大灯珠数、RMT通道、gpio口：

```c
typedef struct {
    uint32_t max_leds;   /*!< Maximum LEDs in a single strip */
    led_strip_dev_t dev; /*!< LED strip device (e.g. RMT channel, PWM channel, etc) */
} led_strip_config_t;
```

利用 `led_strip_init` 函数可以初始化 `led_strip_config_t`：

```c
led_strip_t * led_strip_init(uint8_t channel, uint8_t gpio, uint16_t led_num);
```

此外，该库还定义了 led_strip_s 结构体，用于控制灯带，该结构体内含如下函数：

```c
/**
 * 设置特定灯珠的 RGB 
 * strip: LED灯珠，即上面的结构体
 * index: 灯珠编号
 * red、green、blue：灯珠亮度，WS2812 能接受的最大亮度为 255
*/
esp_err_t (*set_pixel)(led_strip_t *strip, uint32_t index, uint32_t red, uint32_t green, uint32_t blue);
```

```c
/**
 * 设置好RGB后，调用该函数刷新灯珠
 * timeout_ms: timeout value for refreshing task
*/
esp_err_t (*refresh)(led_strip_t *strip, uint32_t timeout_ms);
```

```c
/**
 * 关闭所用灯珠
 * timeout_ms: timeout value for clearing task
*/
esp_err_t (*clear)(led_strip_t *strip, uint32_t timeout_ms);
```

```c
/**
 * 释放资源
*/
esp_err_t (*del)(led_strip_t *strip);
```
