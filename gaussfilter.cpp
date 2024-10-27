#include "gaussfilter.h"
#include <cmath>
#include <vector>

std::vector<std::vector<double>> createGaussCore() {
    return {
        {1 / 16.0, 2 / 16.0, 1 / 16.0},
        {1 / 16.0, 4 / 16.0, 2 / 16.0},
        {1 / 16.0, 2 / 16.0, 1 / 16.0}
    };
}

BMPImage useGaussFilter(const BMPImage& image) {
    BMPImage filteredImage = image;
    int width = image.width;
    int height = image.height;
    int bytesPerPixel = image.bytesPerPixel;

    std::vector<std::vector<double>> core = createGaussCore();
    int coreSize = core.size();
    int coreRadius = coreSize / 2;

    for (int y = coreRadius; y < height - coreRadius; ++y) {
        for (int x =  coreRadius; x < width - coreRadius; ++x) {
            double sumR = 0, sumG = 0, sumB = 0;
            for (int ky = -coreRadius; ky <= coreRadius; ++ky) {
                for (int kx = - coreRadius; kx <= coreRadius; ++kx) {
                    int pixelX = x + kx;
                    int pixelY = y + ky;
                    int pixelIndex = (pixelY * width + pixelX) * bytesPerPixel;

                    uint8_t r = image.pixelData[pixelIndex];
                    uint8_t g = image.pixelData[pixelIndex + 1];
                    uint8_t b = image.pixelData[pixelIndex + 2];

                    double weight = core[ky + coreRadius][kx + coreRadius];
                    sumR += r * weight;
                    sumG += g * weight;
                    sumB += b * weight;
                }
            }
        }
    }
    return filteredImage;
}
