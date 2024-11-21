#ifndef BMP_H
#define BMP_H

#include <string>
#include <vector>

struct BMPHeader {
    uint16_t fileType;        
    uint32_t fileSize;        
    uint16_t reserved1;       
    uint16_t reserved2;       
    uint32_t offsetData;      
    uint32_t size;            
    int32_t width;            
    int32_t height;           
    uint16_t planes;          
    uint16_t bitsPerPixel;   
    uint32_t compression;     
    uint32_t imageSize;       
    int32_t xPixelsPerMeter;  
    int32_t yPixelsPerMeter; 
    uint32_t colorsUsed;      
    uint32_t colorsImportant; 
};

struct BMPImage {
    BMPHeader header;
    std::vector<uint8_t> data;
    int width;
    int height;
    int bytesPerPixel;
    std::vector<uint8_t> pixelData;
    void load(const std::string& filename);
    void save(const std::string& filename);
};

BMPImage loadBMP(const std::string& filename);
void saveBMP(const std::string& filename);

#endif