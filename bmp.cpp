#include "bmp.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <iostream>

#pragma pack(push, 1) 
struct BMPHeader {
    uint16_t fileType;         
    uint32_t fileSize;         
    uint32_t reserved;         
    uint32_t dataOffset;       
    uint32_t headSize;         
    int32_t width;             
    int32_t height;            
    uint16_t planes;           
    uint16_t bitsPerPixel;     
    uint32_t compression;      
    uint32_t imageSize;        
    uint32_t xPixelsPerMeter;  
    uint32_t yPixelsPerMeter;  
    uint32_t totalColors;      
    uint32_t importantColors;  
};
#pragma pack(pop)

BMPImage loadBMP(const std::string& filename) {
    BMPImage image;
    BMPHeader header;

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("The file could not be opened for reading: " + filename);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (!file) {
        throw std::runtime_error("Failed to read BMP header from: " + filename);
    }

    if (header.fileType != 0x4D42) {
        throw std::runtime_error("This file is not BMP: " + filename);
    }

    if (header.width <= 0 || header.height <= 0) {
        throw std::runtime_error("Invalid image dimensions: width or height is non-positive.");
    }

    image.width = header.width;
    image.height = header.height;
    image.bytesPerPixel = header.bitsPerPixel / 8;

    // Вычисляем размер строки с учетом паддинга
    size_t rowSize = ((header.bitsPerPixel / 8 * image.width + 3) & (~3));

    // Размер данных изображения
    size_t imageSize = rowSize * image.height;
    image.pixelData.resize(imageSize);

    file.seekg(header.dataOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(image.pixelData.data()), imageSize);

    if (!file) {
        throw std::runtime_error("Error reading image data from file: " + filename);
    }

    return image;
}

void saveBMP(const std::string& filename, const BMPImage& image) {
    BMPHeader header;
    header.fileType = 0x4D42; // 'BM'
    header.width = image.width;
    header.height = image.height;
    header.bitsPerPixel = image.bytesPerPixel * 8;
    header.planes = 1;
    header.compression = 0; 

    // Вычисляем размер строки с учетом паддинга
    size_t rowSize = ((header.bitsPerPixel / 8 * header.width + 3) & (~3));
    size_t padding = rowSize - (image.width * image.bytesPerPixel);
    header.imageSize = rowSize * header.height; // Общий размер изображения с паддингом
    header.fileSize = sizeof(BMPHeader) + header.imageSize; // Общий размер файла
    header.dataOffset = sizeof(BMPHeader); // Смещение данных

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("The file could not be opened for writing: " + filename);
    }

    // Запись заголовка
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));

    // Запись данных изображения с учетом паддинга
    for (int i = 0; i < image.height; ++i) {
        file.write(reinterpret_cast<const char*>(image.pixelData.data() + i * image.width * image.bytesPerPixel), image.width * image.bytesPerPixel);
        
        // Запись паддинга
        std::vector<uint8_t> pad(padding, 0); // Создаем вектор паддинга
        file.write(reinterpret_cast<const char*>(pad.data()), padding); // Записываем паддинг
    }

    if (!file) {
        throw std::runtime_error("Error when writing image data to file: " + filename);
    }
}