# color

color.h 中有色彩变换相关的函数。由于色彩理论很复杂，我暂时没时间进行优化，相关的计算优化可以参考 [ESPxRGB](https://github.com/technosf/ESPxRGB)

色彩变换的介绍：

- <https://www.zhihu.com/question/265265004/answer/291580901>
- <https://www.zhihu.com/question/336949411>

此处我们主要关注 HSV 与 RGB. 后者很容易理解，LED 的三个色彩就是 RGB，前者则是符合人类直觉的色彩模型。那为什么选择 HSV 而不是 HSL 呢？因为如果需要调亮度，那么最亮时不应该为全白，HSL的L分量最大时为全白，因此不选择 HSL.

## HSV

**HSV** 代表 **Hue色相**, **Saturation饱和度**, **Value亮度**. 有时候 HSV 也叫 HSB，前两个字母的含义不变，B 代表 **Brightness**.

- 色相（H,hue）：在0~360°的标准色轮上，色相是按位置度量的。在通常的使用中，色相是由颜色名称标识的，比如红、绿或橙色。黑色和白色无色相。
- 饱和度（S,saturation）：表示色彩的纯度，为0时为灰色。白、黑和其他灰色色彩都没有饱和度的。在最大饱和度时，每一色相具有最纯的色光。取值范围0～100%
- 亮度（B,brightness或V,value）：是色彩的明亮度。为0时即为黑色。最大亮度是色彩最鲜明的状态。取值范围0～100%。

> 以上内容摘自：[色彩空间中的 HSL、HSV、HSB 有什么区别？ - AK23的回答 - 知乎](https://www.zhihu.com/question/22077462/answer/342570140)

RGB 到 HSV 的变换过程可以用下面这张图来表示（来源：[HSL and HSV - Wikipedia](https://en.wikipedia.org/wiki/HSL_and_HSV#/media/File:Hsl-and-hsv.svg)）：

![HSL and HSV](/docs/images/Hsl-and-hsv.svg)

首先，假设 R,G,B 分别是三维空间中的 x,y,z 轴。现在我们从原点(0,0,0)到对角的顶点(255,255,255)连出一条直线，也就是一条体对角线。这条对角线就可以说是一条明度轴了，原点最暗，另一端最亮。

![RGB 立方体](/docs/images/RGB_cube.jpg)

我们以这个轴为中心把这个立方体立起来，那么就会形成一个正六边形投影。

![](/docs/images/HSL-HSV_hue_and_chroma.svg)

以红色为极轴，全红时为 1，建立极坐标。则颜色的极角近似是色相（Hue），而极径近似是色度（Chroma）。色度可以理解成和饱和度（Saturation）类似的东西。

但注意，上面只是近似，但如果仔细观察会发现，六个角的极径会比边上的点的极径大，这显然不方便比较（因为按道理六边形上各点的色度相同。故我们将色度定义为比值 $OP/OP'$，即“某点极径”与“同极角下最大极径”之比，或者“某点所在的六边形半径”与“最大六边形半径”之比。在这个定义下，某一颜色的色度 $C$ 可以定义为 R G B 分量中的最大值减最小值。

$$
M = \max(R,G,B)
$$

$$
m=\min(R,G,B)
$$

$$
C={\rm range}(R,G,B)=M-m
$$

这个要直接证明并不难（利用“六边形半径之比”的定义来证明）。Wikipedia 上有个更直白的证明过程：

1. 在三维空间中考虑，如果某一颜色的 R=G=B，那么它会落在黑白那条轴上，色度为 0. 
2. 对于 (R,G,B) 和 (R-m,G-m,B-m)，两种颜色的色度不变，只在明暗上有区别。
3. 如果某个颜色的 RGB 分量中有一个分量为 0，那么这个颜色的色度就是剩下两个分量的最大值（因为最大值决定了六边形的半径）。

综合上面三点，就得到 $C=M-m$.

而对于色度（Hue），在上面的定义中同样是近似。准确的定义如下：

$$
H'=
\begin{cases}
    \text{undefined} & C=0\\
    \frac{G-B}{C} {\rm mod} 6 & M=R\\
    \frac{B-R}{C}+2 & M=G\\
    \frac{R-G}{C}+4 & M=B
\end{cases}
$$

$$
H=60^\circ \times H'
$$

乘以 60 是为了从分数转化为角度，而分子相减除以 $C$ 则是求在边上的比例。我们只需要将 RGB 分量按大小中的顺序首尾相接即可证明。

在上面的准确定义下，色相平面就会由六角形变为圆形：

![色相平面由六角形变为圆形](/docs/images/Hsv-hexagons-to-circles.svg)

下面讨论对黑白那条轴的分量，不同色彩模型采用了不同方法。

1. HSV 认为 $V=\max(R,G,B)=M$，使得白色与RGB原色的亮度一致（下图b）
2. HSL 认为 $L=(M+m)/2$（下图c）
3. 其余两个请看 [Wikipidea](https://en.wikipedia.org/wiki/HSL_and_HSV#Lightness)

![黑白轴的处理](/docs/images/Hsl-hsv_chroma-lightness_slices.svg)

注意到在上图 b 中，有些地方是灰色的，说明此处没有色彩定义。为了弥补这些灰色，定义饱和度 $S=C/V$，使得截面从三角形变为方形（下图）

![饱和度](/docs/images/Hsl-hsv_saturation-lightness_slices.svg)

总结一下就是 RGB 到 HSV 的过程如下：$R,G,B\in [0,1]$

1. $V=M=\max(R,G,B)$
2. $m=\min(R,G,B)$
3. $C=V-m$
4. $$
   H=\begin{cases}
    0 & C=0\\
    60^\circ \cdot (0+\frac{G-B}{C}) & V=R\\
    60^\circ \cdot (2+\frac{B-R}{C}) & V=G\\
    60^\circ \cdot (4+\frac{R-G}{C}) & V=B\\
   \end{cases}
   $$
5. $$
   S=\begin{cases}
    0 & V=0\\
    C/V & V\neq 0
   \end{cases}
   $$

了解完 RGB 到 HSV 的变换过程后，下面给出逆变换公式：给定 $H\in [0^\circ,360^\circ]$，$S\in[0,1]$，$V\in[0,1]$，则可以求得色度（chroma）

$$
C=V\times S = V\times \frac{C}{V}
$$

然后逆推之前的分段函数：

$$
H'=\frac{H}{60^\circ}
$$

$$
X=C\times(1-\vert H' {\rm mod} 2 - 1 \vert)
$$

$$
(R_1,G_1,B_1)=\begin{cases}
    (C,X,0) & 0 \leq H'\lt 1\\
    (X,C,0) & 1 \leq H'\lt 2\\
    (0,C,X) & 2 \leq H'\lt 3\\
    (0,X,C) & 3 \leq H'\lt 4\\
    (X,0,C) & 4 \leq H'\lt 5\\
    (C,0,X) & 5 \leq H'\lt 6\\
\end{cases}
$$

然后再加上最小值

$$
m=V-C=M-(M-m)
$$

$$
(R,G,B)=(R_1+m,G_1+m,B_1+m)
$$

网上还有另一种转换方法，原理是一样的：

$$
H'=\lfloor \frac{h}{60} \rfloor {\rm mod} 6
$$

$$
f=\frac{h}{60}-H'
$$

$$
m=V\times (1-S)=M-C
$$

$$
q=V\times(1-f\times S)
$$

$$
t=V\times(1-(1-f)\times S)
$$

$$
(R,G,B)=\begin{cases}
    (V,t,m) & H'=0\\
    (q,V,m) & H'=1\\
    (m,V,t) & H'=2\\
    (m,q,V) & H'=3\\
    (t,m,V) & H'=4\\
    (V,m,q) & H'=5\\
\end{cases}
$$

$V$（即 $M$）和 $m$ 分别是 RGB 中的最大值和最小值，而 $q,t$ 是中间值。为什么会有两个中间值呢？假如 $V=R$，那么根据公式：

$$
H=60^\circ \cdot (0+\frac{G-B}{C})
$$

由于 $G$ 和 $B$ 都有可能是中间值，故有两种情况。

## 整型 HSV 与 RGB 转换

上面的转化过程中不可避免地会出现分数（浮点数），而大部分MCU都没有浮点数计算能力，就算有其所需的时钟周期也比整数计算长，因此如何用整数实现转换，并且加快计算速度、减小误差，是一个重要议题。

> ESP32C3采用的是 RV32IMC ISA，支持 32 位乘除法。

中规中矩的做法是直接用上面的公式：

```c
// MIT License
// Copyright (c) 2021 ZhiliangMa
// Copyright (c) https://github.com/ZhiliangMa/easyio-lib-for-esp32

/**
 * @brief 将HSV颜色空间转换为RGB颜色空间
 *      - 因为HSV使用起来更加直观、方便，所以代码逻辑部分使用HSV。但WS2812B RGB-LED灯珠的驱动使用的是RGB，所以需要转换。
 * 
 * @param  h HSV颜色空间的H：色调。单位°，范围0~360。（Hue 调整颜色，0°-红色，120°-绿色，240°-蓝色，以此类推）
 * @param  s HSV颜色空间的S：饱和度。单位%，范围0~100。（Saturation 饱和度高，颜色深而艳；饱和度低，颜色浅而发白）
 * @param  v HSV颜色空间的V：明度。单位%，范围0~100。（Value 控制明暗，明度越高亮度越亮，越低亮度越低）
 * @param  r RGB-R值的指针
 * @param  g RGB-G值的指针
 * @param  b RGB-B值的指针
 *
 * Wiki: https://en.wikipedia.org/wiki/HSL_and_HSV
 *
 */
void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v,
                       uint32_t *r, uint32_t *g, uint32_t *b)
{
    h %= 360; // h -> [0,360]
    uint32_t rgb_max = v * 2.55f;
    uint32_t rgb_min = rgb_max * (100 - s) / 100.0f;

    uint32_t i = h / 60;
    uint32_t diff = h % 60;

    // RGB adjustment amount by hue
    uint32_t rgb_adj = (rgb_max - rgb_min) * diff / 60;

    switch (i) {
    case 0:
        *r = rgb_max;
        *g = rgb_min + rgb_adj;
        *b = rgb_min;
        break;
    case 1:
        *r = rgb_max - rgb_adj;
        *g = rgb_max;
        *b = rgb_min;
        break;
    case 2:
        *r = rgb_min;
        *g = rgb_max;
        *b = rgb_min + rgb_adj;
        break;
    case 3:
        *r = rgb_min;
        *g = rgb_max - rgb_adj;
        *b = rgb_max;
        break;
    case 4:
        *r = rgb_min + rgb_adj;
        *g = rgb_min;
        *b = rgb_max;
        break;
    default:
        *r = rgb_max;
        *g = rgb_min;
        *b = rgb_max - rgb_adj;
        break;
    }
}
```

当然上面的代码也不是很好，因为 r,g,b 一般是 0~255，没必要用 uint32；而 h 应该越大越好，范围不应该限制在 360，而是利用整个 uint32（但是否应该设置为 0~2^32-1 呢？存疑）；rgb最大值是255，因此 v 应该用 uint8；s 和 v 一样也应该是 uint8. 因此理想的参数应该是

```c
#define HSV_HUE_SEXTANT		256
#define HSV_HUE_STEPS		(6 * HSV_HUE_SEXTANT)

#define HSV_HUE_MIN		0
#define HSV_HUE_MAX		(HSV_HUE_STEPS - 1)
#define HSV_SAT_MIN		0
#define HSV_SAT_MAX		255
#define HSV_VAL_MIN		0
#define HSV_VAL_MAX		255

void led_strip_hsv2rgb(uint32_t h, uint8_t s, uint8_t v,
                       uint8_t *r, uint8_t *g, uint8_t *b)
{
    h %= HSV_HUE_STEPS; // h -> [0,360]
    uint8_t rgb_max = v;
    uint8_t rgb_min = rgb_max * (HSV_SAT_MAX - s) / HSV_SAT_MAX.0f;

    uint8_t i = h / HSV_HUE_SEXTANT;
    uint8_t diff = h % HSV_HUE_SEXTANT;

    // RGB adjustment amount by hue
    uint8_t rgb_adj = (rgb_max - rgb_min) * diff / HSV_HUE_SEXTANT;

    switch (i) {
    case 0:
        *r = rgb_max;
        *g = rgb_min + rgb_adj;
        *b = rgb_min;
        break;
    case 1:
        *r = rgb_max - rgb_adj;
        *g = rgb_max;
        *b = rgb_min;
        break;
    case 2:
        *r = rgb_min;
        *g = rgb_max;
        *b = rgb_min + rgb_adj;
        break;
    case 3:
        *r = rgb_min;
        *g = rgb_max - rgb_adj;
        *b = rgb_max;
        break;
    case 4:
        *r = rgb_min + rgb_adj;
        *g = rgb_min;
        *b = rgb_max;
        break;
    default:
        *r = rgb_max;
        *g = rgb_min;
        *b = rgb_max - rgb_adj;
        break;
    }
}
```

