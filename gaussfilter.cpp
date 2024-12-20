#include "gaussfilter.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<std::vector<double>> createGaussCore(int size, double sigma) {
    if (size % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd.");
    }

    int radius = size / 2;
    std::vector<std::vector<double>> core(size, std::vector<double>(size));
    double sum = 0.0;

    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            double value = std::exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            core[y + radius][x + radius] = value;
            sum += value;
        }
    }

    for (auto& row : core) {
        for (double& val : row) {
            val /= sum;
        }
    }

    return core;
}

BMPImage useGaussFilter(const BMPImage& image, int coreSize, double sigma) {
    if (coreSize % 2 == 0) {
        throw std::invalid_argument("Core size must be odd");
    }

    BMPImage filteredImage;

    filteredImage.setHeader(image.getHeader());
    filteredImage.setInfoHeader(image.getInfoHeader());

    int width = image.getWidth();
    int height = image.getHeight();
    int bytesPerPixel = image.getBytesPerPixel();

    filteredImage.setPixelData(std::vector<uint8_t>(width * height * bytesPerPixel, 0));

    const std::vector<uint8_t>& srcPixelData = image.getPixelData();
    std::vector<uint8_t> destPixelData = filteredImage.getPixelData();

    std::vector<std::vector<double>> core = createGaussCore(coreSize, sigma);
    int coreRadius = coreSize / 2;

    for (int y = coreRadius; y < height - coreRadius; ++y) {
        for (int x = coreRadius; x < width - coreRadius; ++x) {
            double sumR = 0.0, sumG = 0.0, sumB = 0.0;

            for (int ky = -coreRadius; ky <= coreRadius; ++ky) {
                for (int kx = -coreRadius; kx <= coreRadius; ++kx) {
                    int pixelX = x + kx;
                    int pixelY = y + ky;

                    if (pixelX < 0 || pixelX >= width || pixelY < 0 || pixelY >= height) {
                        continue; 
                    }

                    int pixelIndex = (pixelY * width + pixelX) * bytesPerPixel;

                    uint8_t r = srcPixelData[pixelIndex];
                    uint8_t g = srcPixelData[pixelIndex + 1];
                    uint8_t b = srcPixelData[pixelIndex + 2];

                    double weight = core[ky + coreRadius][kx + coreRadius];
                    sumR += r * weight;
                    sumG += g * weight;
                    sumB += b * weight;
                }
            }

            int newPixelIndex = (y * width + x) * bytesPerPixel;
            destPixelData[newPixelIndex]     = static_cast<uint8_t>(std::clamp(sumR, 0.0, 255.0));
            destPixelData[newPixelIndex + 1] = static_cast<uint8_t>(std::clamp(sumG, 0.0, 255.0));
            destPixelData[newPixelIndex + 2] = static_cast<uint8_t>(std::clamp(sumB, 0.0, 255.0));
        }
    }

    filteredImage.setPixelData(destPixelData);
    return filteredImage;
}