#include "bmp.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

const BMPHeader& BMPImage::getHeader() const {
    return header;
}

const BMPInfoHeader& BMPImage::getInfoHeader() const {
    return infoHeader;
}

const std::vector<uint8_t>& BMPImage::getPixelData() const {
    return pixelData;
}

int BMPImage::getWidth() const {
    return infoHeader.width;
}

int BMPImage::getHeight() const {
    return infoHeader.height;
}

int BMPImage::getBytesPerPixel() const {
    return infoHeader.bitsPerPixel / 8;
}

void BMPImage::setHeader(const BMPHeader& hdr) {
    header = hdr;
}

void BMPImage::setInfoHeader(const BMPInfoHeader& infoHdr) {
    infoHeader = infoHdr;
}

void BMPImage::setPixelData(const std::vector<uint8_t>& data) {
    pixelData = data;
}

void BMPImage::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (file.gcount() != sizeof(BMPHeader) || header.fileType != 0x4D42) {
        throw std::runtime_error("Error: File is not a valid BMP or header is corrupted");
    }

    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (file.gcount() != sizeof(BMPInfoHeader)) {
        throw std::runtime_error("Error: Failed to read BMP info header");
    }

   if (infoHeader.imageSize == 0) {
       infoHeader.imageSize = infoHeader.width * infoHeader.height * (infoHeader.bitsPerPixel / 8);
   }

   if (header.offsetData < sizeof(BMPHeader) + sizeof(BMPInfoHeader)) {
       throw std::runtime_error("Error: Invalid offset data in BMP header");
   }

   pixelData.resize(infoHeader.imageSize);
   file.seekg(header.offsetData, std::ios::beg);

   int rowSize = ((infoHeader.bitsPerPixel * infoHeader.width + 31) / 32) * 4; 
   int padding = rowSize - (infoHeader.width * getBytesPerPixel());

   for (int y = 0; y < infoHeader.height; ++y) {
       file.read(reinterpret_cast<char*>(pixelData.data()) + y * rowSize, infoHeader.width * getBytesPerPixel());
       if (file.gcount() != infoHeader.width * getBytesPerPixel()) {
           throw std::runtime_error("Error: Failed to read pixel data");
       }
       file.ignore(padding);
   }

   std::cout << "Loaded BMP File: " << filename << "\n";
}

void BMPImage::save(const std::string& filename) {
   std::ofstream file(filename, std::ios::binary);

   if (!file) {
       throw std::runtime_error("Error: Cannot open file " + filename);
   }

   int rowSize = ((infoHeader.bitsPerPixel * infoHeader.width + 31) / 32) * 4; 
   int padding = rowSize - (infoHeader.width * getBytesPerPixel());

   header.fileSize = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + pixelData.size() + (padding * infoHeader.height);
   header.offsetData = sizeof(BMPHeader) + sizeof(BMPInfoHeader);

   file.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));
   file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BMPInfoHeader));

   for (int y = 0; y < infoHeader.height; ++y) {
       int srcIndex = y * infoHeader.width * getBytesPerPixel();
       file.write(reinterpret_cast<const char*>(pixelData.data()) + srcIndex, infoHeader.width * getBytesPerPixel());

       for (int i = 0; i < padding; ++i) {
           file.put(0); 
       }
   }

   std::cout << "Saved BMP File: " << filename << "\n";
}