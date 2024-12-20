#ifndef GAUSSFILTER_H
#define GAUSSFILTER_H

#include "bmp.h"

std::vector<std::vector<double>> createGaussCore(int size, double sigma);
BMPImage useGaussFilter(const BMPImage& image, int coreSize, double sigma);

#endif