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

RGB 到 HSV 的变换过程可以用下面这张图来表示：

![HSL and HSV](/docs/images/Hsl-and-hsv.svg)
