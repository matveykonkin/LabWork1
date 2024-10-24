#ifndef BMP_H
#define BMP_H

#include <string>
#include <vector>

struct BMPImage {
    int width;
    int height;
    int bytesPerPixel;
    std::vector<uint8_t> pixelData;
};

BMPImage loadBMP(const std::string& filename);
void saveBMP(const std::string& filename, const BMPImage& image);

#endif