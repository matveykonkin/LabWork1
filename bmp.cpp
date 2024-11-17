#include "bmp.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

void BMPImage::load( std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    // Считываем заголовок BMP
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    if (header.fileType != 0x4D42) { // Проверка на 'BM'
        throw std::runtime_error("Error: File is not a valid BMP");
    }

    // Отладочный вывод
    std::cout << "Loaded BMP File: " << filename << "\n";
    std::cout << "FileType: " << std::hex << header.fileType << "\n";
    std::cout << "FileSize: " << header.fileSize << "\n";
    std::cout << "OffsetData: " << header.offsetData << "\n";
    std::cout << "Width: " << header.width << "\n";
    std::cout << "Height: " << header.height << "\n";
    std::cout << "BitsPerPixel: " << header.bitsPerPixel << "\n";

    // Проверка правильности значений
    if (header.width <= 0 || header.height <= 0) {
        throw std::runtime_error("Error: Invalid image dimensions");
    }
}

void BMPImage::save( std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    // Записываем размер файла и смещение данных
    size_t rowSize = ((header.bitsPerPixel / 8 * header.width + 3) & ~3);
    size_t dataSize = rowSize * header.height;

    header.fileSize = sizeof(BMPHeader) + dataSize;
    header.offsetData = sizeof(BMPHeader);  // Позиция данных сразу после заголовка

    // Записываем заголовок
    file.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));

    // Записываем данные
    file.write(reinterpret_cast<const char*>(data.data()), dataSize);

    // Отладочный вывод
    std::cout << "Saved BMP File: " << filename << "\n";
    std::cout << "  FileType: " << std::hex << header.fileType << "\n";
    std::cout << "  FileSize: " << header.fileSize << "\n";
    std::cout << "  OffsetData: " << header.offsetData << "\n";
    std::cout << "  Width: " << header.width << "\n";
    std::cout << "  Height: " << header.height << "\n";
    std::cout << "  BitsPerPixel: " << header.bitsPerPixel << "\n";
}