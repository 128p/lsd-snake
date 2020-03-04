#include "util.h"

int darken_hex(uint32_t color, int div) {
    unsigned char red   = ((color >> 16) & 255) / div;
    unsigned char green = ((color >> 8) & 255) / div;
    unsigned char blue  = (color & 255) / div;

    return (red << 16) | (green << 8) | blue;
}
