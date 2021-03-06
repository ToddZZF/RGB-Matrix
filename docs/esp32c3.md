# esp32c3

## 资料

- [合宙ESP32C3-CORE开发板](https://wiki.luatos.com/chips/esp32c3/board.html)
- [ESP32­C3 datasheet](https://www.espressif.com.cn/sites/default/files/documentation/esp32-c3_datasheet_cn.pdf)
- [ESP32­C3 技术参考手册](https://www.espressif.com.cn/sites/default/files/documentation/esp32-c3_technical_reference_manual_cn.pdf)
- [esp-idf 编程指南](https://docs.espressif.com/projects/esp-idf/zh_CN/v4.4.1/esp32c3/get-started/index.html)

## 引脚分配

|引脚编号|GPIO|复用功能|注意|
|------|----|---|---|
|05|18|USB_D+|简约版下载口|
|06|19|USB_D-|简约版下载口|
|08|21|UART0_RX|经典款下载口|
|09|20|UART0_TX|经典款下载口|
|24|11|VDD_SPI|设置熔断后才能作为GPIO|
|29|8|PWM04|不能外部下拉，否则不能用串口下载|
|30|9|BOOT|按下时下载，上电前不能下拉|
|（未引出）|12~17|片内FLASH||

## 引脚分配

| 外设 | 资源 | 引脚 |工作电压|价格|
|-----|------|-----|------|----|
|WS2812 三色灯| I2S TX|  |5V|取决于数量|
|INMP441 麦克风| I2S RX|  |3.3V|￥9|
|SHT3X 温湿度|I2C（0x44/0x45）| | 3.3V|￥9.8|
|SGP30 空气质量|I2C（0x58）||3.3V|￥35|
|BH1750 光照|I2C（0x46/0xB8）||3.3V|￥6.8|