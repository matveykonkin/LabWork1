#include "image.h"
#include <iostream>

BMPImage rotate90Clockwise(const BMPImage& image) {
    BMPImage rotatedImage;

	rotatedImage.setHeader(image.getHeader());
	BMPInfoHeader rotatedInfoHeader = image.getInfoHeader();
	rotatedInfoHeader.width = image.getHeight();
	rotatedInfoHeader.height = image.getWidth();
	rotatedImage.setInfoHeader(rotatedInfoHeader);

	int bytesPerPixel = image.getBytesPerPixel();
	int rowSize = ((rotatedInfoHeader.bitsPerPixel * rotatedInfoHeader.width + 31) / 32) * 4; 
	std::vector<uint8_t> destPixelData(rowSize * rotatedInfoHeader.height);

	const std::vector<uint8_t>& srcPixelData = image.getPixelData();

	for (int y = 0; y < image.getHeight(); ++y) {
		for (int x = 0; x < image.getWidth(); ++x) {
			int srcIndex = (y * image.getWidth() + x) * bytesPerPixel;
			int destX = image.getHeight() - 1 - y; 
			int destY = x;
			int destIndex = (destY * rowSize + destX * bytesPerPixel);

			for (int i = 0; i < bytesPerPixel; ++i) {
				destPixelData[destIndex + i] = srcPixelData[srcIndex + i];
			}
		}
	}

	rotatedImage.setPixelData(destPixelData);
	return rotatedImage;
}

BMPImage rotate90CounterClockwise(const BMPImage& image) {
	BMPImage rotatedImage;

	rotatedImage.setHeader(image.getHeader());
	BMPInfoHeader rotatedInfoHeader = image.getInfoHeader();
	rotatedInfoHeader.width = image.getHeight();
	rotatedInfoHeader.height = image.getWidth();
	rotatedImage.setInfoHeader(rotatedInfoHeader);

	int bytesPerPixel = image.getBytesPerPixel();
	int rowSize = ((rotatedInfoHeader.bitsPerPixel * rotatedInfoHeader.width + 31) / 32) * 4; 
	std::vector<uint8_t> destPixelData(rowSize * rotatedInfoHeader.height);

	const std::vector<uint8_t>& srcPixelData = image.getPixelData();

	for (int y = 0; y < image.getHeight(); ++y) {
		for (int x = 0; x < image.getWidth(); ++x) {
			int srcIndex = (y * image.getWidth() + x) * bytesPerPixel;
			int destX = y; 
			int destY = image.getWidth() - 1 - x;
			int destIndex = (destY * rowSize + destX * bytesPerPixel);

			for (int i = 0; i < bytesPerPixel; ++i) {
				destPixelData[destIndex + i] = srcPixelData[srcIndex + i];
			}
		}
	}

	rotatedImage.setPixelData(destPixelData);
	return rotatedImage;
}