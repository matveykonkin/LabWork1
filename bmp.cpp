#include "bmp.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstdint>

struct BMPHeader {
    uint16_t fileType{0x4D42};
    uint32_t fileSize{0};
    uint32_t reserved{0};
    uint32_t dataOffset{54};
    uint32_t headSize{40};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bytesPerPixel{24};
    uint32_t comression{0};
    uint32_t imageSize{0};
    uint32_t xPixelPerMeter{0};
    uint32_t yixelPerMeter{0};
    uint32_t totalColors{0};
    uint32_t importantColors{0};
};

BMPImage loadBMP(const std::string& filename) {
    BMPImage image;
    BMPHeader header;

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("The file could not bo opened for reading" + filename);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (header.fileType != 0x4D42) {
        throw std::runtime_error("This file is not BMP" + filename);
    }

    image.width = header.width;
    image.height = header.height;
    image.bytesPerPixel = header.bytesPerPixel / 8;
    image.pixelData.resize(image.width * image.height * image.bytesPerPixel);

    if (!file) {
        throw std::runtime_error("Error reading image data from a file" + filename);
    }
    return image;
}

void saveBMP(const std::string& filename, const BMPImage& image) {
    BMPHeader header;
    header.fileSize = sizeof(BMPHeader) + image.pixelData.size();
    header.width = image.width;
    header.height = image.height;
    header.bytesPerPixel = image.bytesPerPixel * 8;
    header.fileSize = image.pixelData.size();

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("The file could not be opened for writing" + filename);
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(image.pixelData.data()), image.pixelData.size());

    if (!file) {
        throw std::runtime_error("Error when writing image data to a file" + filename);
    }
}
