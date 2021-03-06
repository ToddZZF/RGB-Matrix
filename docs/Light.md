# Light

[AWTRIX](https://awtrixdocs.blueforcer.de/#/) 采用的是光敏电阻（ADC测量电压）的方法来获取亮度。这个好处就是电路简单，而且光敏电阻便宜（10个3元左右），坏处是无法获取精确数值。

另一种方法是采用光照传感器。光照传感器也分为模拟输出（TEMT6000）和数字（BH1750）输出两类。模拟输出的光照传感器与光敏电阻类似，但可以获取精确数值；数字输出的光照传感器的电路较复杂（也就多两三个电阻和电容），但它可以与其它传感器共用 i2c 引脚，无需额外占用引脚。价格上这两种环境光照传感器是一样的（不考虑外围电路）。

||光敏电阻|光照传感器（模拟）|光照传感器（数字）|
|---|---|---|---|
|电路|简单|简单|复杂|
|精度|低|高|高|
|占用引脚|ADC|ADC|i2c|
|成本|低|高|高|

这么看来，模拟输出的光照传感器高不成低不就，没必要用它（或者如果你懒得写驱动代码，懒得画外围电路，又想获得精确数值，那可以用）。至于另外两个嘛，如果是自用肯定选择好的；如果要量产那选便宜的。

本设计中三种都会画上去（但不可以共用）。
