/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#pragma once

#include <iostream>
#include <vector>
#include "kernel.h"

struct Color
{
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

#pragma pack(push, 1)
struct BMPFileHeader
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct BMPInfoHeader
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xpelsPerMeter;
    int32_t ypelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};
#pragma pack(pop)

class Image
{
public:
    Image(int width, int height);
    ~Image();

    int GetWidth() const;
    int GetHeight() const;
    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);
    void Read(const char* path);
    void Export(const char* path) const;
    void ApplyGaussianBlur(int radius, float sigma);

private:
    int m_width;
    int m_height;
    std::vector<Color> m_pixels;
};