#include "bmp.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

void BMPImage::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    if (header.fileType != 0x4D42) { 
        throw std::runtime_error("Error: File is not a valid BMP");
    }

    std::cout << "Loaded BMP File: " << filename << "\n";
    std::cout << "FileType: " << std::hex << header.fileType << "\n";
    std::cout << "FileSize: " << header.fileSize << "\n";
    std::cout << "OffsetData: " << header.offsetData << "\n";
    std::cout << "Width: " << header.width << "\n";
    std::cout << "Height: " << header.height << "\n";
    std::cout << "BitsPerPixel: " << header.bitsPerPixel << "\n";

    if (header.width <= 0 || header.height <= 0) {
        throw std::runtime_error("Error: Invalid image dimensions");
    }
}

void BMPImage::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    size_t rowSize = ((header.bitsPerPixel / 8 * header.width + 3) & ~3);
    size_t dataSize = rowSize * header.height;

    header.fileSize = sizeof(BMPHeader) + dataSize;
    header.offsetData = sizeof(BMPHeader);  

    file.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));

    file.write(reinterpret_cast<const char*>(data.data()), dataSize);

    std::cout << "Saved BMP File: " << filename << "\n";
    std::cout << "  FileType: " << std::hex << header.fileType << "\n";
    std::cout << "  FileSize: " << header.fileSize << "\n";
    std::cout << "  OffsetData: " << header.offsetData << "\n";
    std::cout << "  Width: " << header.width << "\n";
    std::cout << "  Height: " << header.height << "\n";
    std::cout << "  BitsPerPixel: " << header.bitsPerPixel << "\n";
}