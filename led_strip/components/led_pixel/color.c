#include "color.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void hsv2rgb(uint16_t hue, uint8_t saturation, uint8_t value,
             uint8_t *red, uint8_t *green, uint8_t *blue)
{
    uint16_t hi = (hue / 60) % 6;
    uint16_t F = 100 * hue / 60 - 100 * hi;
    uint16_t P = value * (100 - saturation) / 100;
    uint16_t Q = value * (10000 - F * saturation) / 10000;
    uint16_t T = value * (10000 - saturation * (100 - F)) / 10000;

    switch (hi)
    {
    case 0:
        *red = value;
        *green = T;
        *blue = P;
        break;
    case 1:
        *red = Q;
        *green = value;
        *blue = P;
        break;
    case 2:
        *red = P;
        *green = value;
        *blue = T;
        break;
    case 3:
        *red = P;
        *green = Q;
        *blue = value;
        break;
    case 4:
        *red = T;
        *green = P;
        *blue = value;
        break;
    case 5:
        *red = value;
        *green = P;
        *blue = Q;
        break;
    default:
        break;
    }
    *red = *red * 255 / 100;
    *green = *green * 255 / 100;
    *blue = *blue * 255 / 100;
}