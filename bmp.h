#ifndef BMP_H
#define BMP_H

#include <string>
#include <vector>
// Почему было решено сделать это стркутурой? В принципе, учитывая расставленный везде const
// это нормальный вариант, но мне кажется, что наличие инкапсуляции тут скорее плюс, потому что
// так сломаться ничего не сможет никогда, а тут я могу напрямую менять значения в обход интерфейса
struct BMPImage {
    int width;
    int height;
    int bytesPerPixel;
    std::vector<uint8_t> pixelData;
};

BMPImage loadBMP(const std::string& filename);
void saveBMP(const std::string& filename, const BMPImage& image);

#endif
