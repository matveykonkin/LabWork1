#ifndef BMP_H
#define BMP_H

#include <string>
#include <cstdint>
#include <vector>

struct BMPHeader {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetData;
};

struct BMPInfoHeader {
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

class BMPImage {
private:
    BMPHeader header;
    BMPInfoHeader infoHeader;
    std::vector<uint8_t> pixelData;

public:
    const BMPHeader& getHeader() const;
    const BMPInfoHeader& getInfoHeader() const;
    const std::vector<uint8_t>& getPixelData() const;
    int getWidth() const;
    int getHeight() const;
    int getBytesPerPixel() const;

    void setHeader(const BMPHeader& hdr);
    void setInfoHeader(const BMPInfoHeader& infoHdr);
    void setPixelData(const std::vector<uint8_t>& data);

    void load(const std::string& filename);
    void save(const std::string& filename);
};

#endif