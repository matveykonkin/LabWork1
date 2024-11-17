#include "image.h"

BMPImage rotate90Clockwise( BMPImage& image) {
    BMPImage rotatedImage;
    rotatedImage.width = image.height;
    rotatedImage.height = image.width;
    rotatedImage.bytesPerPixel = image.bytesPerPixel;
    rotatedImage.pixelData.resize(rotatedImage.width * rotatedImage.height * rotatedImage.bytesPerPixel);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int srcIndex = (y * image.width + x) * image.bytesPerPixel;
            int destX = image.height - 1 - y;
            int destY = x;
            int destIndex = (destY * rotatedImage.width + destX) * rotatedImage.bytesPerPixel;

            for (int i = 0; i < image.bytesPerPixel; ++i) {
                rotatedImage.pixelData[destIndex + i] = image.pixelData[srcIndex + i];
            }
        }
    }
    return rotatedImage;
}

BMPImage rotate90CounterClockwise( BMPImage& image) {
    BMPImage rotatedImage;
    rotatedImage.width = image.height;
    rotatedImage.height = image.width;
    rotatedImage.bytesPerPixel = image.bytesPerPixel;
    rotatedImage.pixelData.resize(rotatedImage.width * rotatedImage.height * rotatedImage.bytesPerPixel);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int srcIndex = (y * image.width + x) * image.bytesPerPixel;
            int destX = y;
            int destY = image.width - 1 - x;
            int destIndex = (destY * rotatedImage.width + destX) * rotatedImage.bytesPerPixel;

            for (int i = 0; i < image.bytesPerPixel; ++i) {
                rotatedImage.pixelData[destIndex + i] = image.pixelData[srcIndex + i];
            }
        }
    }
    return rotatedImage;
}