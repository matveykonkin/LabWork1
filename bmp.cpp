#include "bmp.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <iostream>

struct BMPHeader {
    uint16_t fileType{0x4D42};        
    uint32_t fileSize{0};             
    uint32_t reserved{0};             
    uint32_t dataOffset{54};          
    uint32_t headSize{40};
    int32_t width{0};                 
    int32_t height{0};                
    uint16_t planes{1};               
    uint16_t bitsPerPixel{24};        
    uint32_t compression{0};        
    uint32_t imageSize{0};            
    uint32_t xPixelsPerMeter{0};      
    uint32_t yPixelsPerMeter{0};      
    uint32_t totalColors{0};          
    uint32_t importantColors{0};      
};

BMPImage loadBMP(const std::string& filename) {
    BMPImage image;
    BMPHeader header;

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("The file could not be opened for reading: " + filename);
    }
    std::cout << "File opened successfully\n";

    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    std::cout << "Header read successfully\n";

    if (header.fileType != 0x4D42) {
        throw std::runtime_error("This file is not BMP: " + filename);
    }

    // Проверяем, что размеры корректны
    if (header.width <= 0 || header.height <= 0) {
        throw std::runtime_error("Invalid image dimensions: width or height is non-positive.");
    }
    
    image.width = header.width;
    image.height = header.height;
    image.bytesPerPixel = header.bitsPerPixel / 8;
    image.pixelData.resize(image.width * image.height * image.bytesPerPixel);

    std::cout << "Image dimensions: " << image.width << "x" << image.height << "\n";

    file.seekg(header.dataOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(image.pixelData.data()), image.pixelData.size());

    if (!file) {
        throw std::runtime_error("Error reading image data from file: " + filename);
    }
    std::cout << "Image data loaded successfully\n";

    return image;
}

void saveBMP(const std::string& filename, const BMPImage& image) {
    BMPHeader header;
    header.fileSize = sizeof(BMPHeader) + image.pixelData.size();
    header.width = image.width;
    header.height = image.height;
    header.bitsPerPixel = image.bytesPerPixel * 8;
    header.imageSize = image.pixelData.size();

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("The file could not be opened for writing: " + filename);
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));

    file.write(reinterpret_cast<const char*>(image.pixelData.data()), image.pixelData.size());

    if (!file) {
        throw std::runtime_error("Error when writing image data to file: " + filename);
    }
}