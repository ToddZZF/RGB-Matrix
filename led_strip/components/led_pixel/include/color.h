#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

void hsv2rgb(uint16_t hue, uint8_t saturation, uint8_t value,
                 uint8_t *red, uint8_t *green, uint8_t *blue);
void rgb2hsv(uint16_t red, uint16_t green, uint16_t blue,
                 uint16_t *h, uint8_t *s, uint8_t *v);

#ifdef __cplusplus
}
#endif