/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
#include "turnimage.h"
#include "kernel.h"

Color::Color() : r(0), g(0), b(0) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::~Color() {}

Image::Image(int width, int height) : m_width(width), m_height(height), m_pixels(width * height) {}

Image::~Image() {}

int Image::GetWidth() const
{
    return m_width;
}

int Image::GetHeight() const
{
    return m_height;
}

Color Image::GetColor(int x, int y) const
{
    return m_pixels[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y)
{
    m_pixels[y * m_width + x] = color;
}

void Image::Read(const char* path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file)
    {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.type != 0x4D42)
    {
        std::cerr << "Not a valid BMP file!" << std::endl;
        return;
    }

    m_width = infoHeader.width;
    m_height = std::abs(infoHeader.height);
    m_pixels.resize(m_width * m_height);

    const int padding = (4 - (m_width * 3) % 4) % 4;
    file.seekg(fileHeader.offset, std::ios::beg);

    bool isFlipped = infoHeader.height > 0;
    for (int y = 0; y < m_height; ++y)
    {
        int row = isFlipped ? (m_height - 1 - y) : y;
        for (int x = 0; x < m_width; ++x)
        {
            unsigned char color[3];
            file.read(reinterpret_cast<char*>(color), 3);
            m_pixels[row * m_width + x] = Color(color[2] / 255.0f, color[1] / 255.0f, color[0] / 255.0f);
        }
        file.ignore(padding);
    }
}

void Image::Export(const char* path) const
{
    std::ofstream file(path, std::ios::binary);
    if (!file)
    {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    BMPFileHeader fileHeader = {};
    BMPInfoHeader infoHeader = {};
    const int padding = (4 - (m_width * 3) % 4) % 4;
    const int dataSize = (m_width * 3 + padding) * m_height;

    fileHeader.type = 0x4D42;
    fileHeader.size = sizeof(fileHeader) + sizeof(infoHeader) + dataSize;
    fileHeader.offset = sizeof(fileHeader) + sizeof(infoHeader);

    infoHeader.size = sizeof(infoHeader);
    infoHeader.width = m_width;
    infoHeader.height = -m_height;
    infoHeader.planes = 1;
    infoHeader.bitsPerPixel = 24;
    infoHeader.imageSize = dataSize;

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    unsigned char paddingBytes[3] = { 0, 0, 0 };
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            const Color& c = GetColor(x, y);
            unsigned char color[3] = {
                static_cast<unsigned char>(c.b * 255),
                static_cast<unsigned char>(c.g * 255),
                static_cast<unsigned char>(c.r * 255)
            };
            file.write(reinterpret_cast<const char*>(color), 3);
        }
        file.write(reinterpret_cast<const char*>(paddingBytes), padding);
    }
}

void Image::ApplyGaussianBlur(int radius, float sigma)
{
    std::vector<std::vector<float>> kernel = Gauss_Kernel::GenerateGaussianKernel(radius, sigma);
    int kernelSize = 2 * radius + 1;
    Image blurredImage(m_width, m_height);

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            Color newColor;
            float totalWeight = 0.0f;

            for (int ky = -radius; ky <= radius; ++ky)
            {
                for (int kx = -radius; kx <= radius; ++kx)
                {
                    int pixelX = std::max(0, std::min(x + kx, m_width - 1));
                    int pixelY = std::max(0, std::min(y + ky, m_height - 1));

                    Color currentColor = GetColor(pixelX, pixelY);
                    newColor.r += currentColor.r * kernel[ky + radius][kx + radius];
                    newColor.g += currentColor.g * kernel[ky + radius][kx + radius];
                    newColor.b += currentColor.b * kernel[ky + radius][kx + radius];
                    totalWeight += kernel[ky + radius][kx + radius];
                }
            }

            newColor.r /= totalWeight;
            newColor.g /= totalWeight;
            newColor.b /= totalWeight;

            blurredImage.SetColor(newColor, x, y);
        }
    }
    m_pixels = std::move(blurredImage.m_pixels);
}