#ifndef IMAGE_H
#define IMAGE_H

#include "bmp.h"

BMPImage rotate90Clockwise(const BMPImage& image);
BMPImage rotate90CounterClockwise(const BMPImage& image);

#endif