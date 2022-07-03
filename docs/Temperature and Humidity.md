# Temperature and Humidity

## 温湿度传感器

温湿度采用常见的 SHT3x，该传感器采用 i2c 通信，外围电路也非常简单。关于它的资料可以在 [DFROBOT SHT30 温湿度传感器](https://wiki.dfrobot.com.cn/_SKU_SEN0330_SHT30_%E6%B8%A9%E6%B9%BF%E5%BA%A6%E4%BC%A0%E6%84%9F%E5%99%A8) 中找到。

由于在常见温度（0~30℃）下，SHT30与SHT31的温度误差一致，故采用较便宜的SHT30。

![SHT30和SHT31的误差](https://img.dfrobot.com.cn/wiki/none/ca01621529e065c044874c25ab9f186d)