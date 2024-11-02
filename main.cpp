#include "bmp.h"
#include "image.h"
#include "gaussfilter.h"
#include <iostream>
#include <string>

int main() {
    try {
        std::string inputFilename = "input.bmp";
        BMPImage image = loadBMP(inputFilename);
        std::cout << "Image is upload " << inputFilename << "\n";

        BMPImage rotatedClockwise = rotate90Clockwise(image);
        std::string rotatedClockwiseFilename = "rClockwise.bmp";
        saveBMP(rotatedClockwiseFilename, rotatedClockwise);
        std::cout << "Image was rotated clockwise and was save " << rotatedClockwiseFilename << "\n";

        BMPImage rotatedCounterClockwise = rotate90CounterClockwise(image);
        std::string rotatedCounterClockwiseFilename = "rCounterClockwise.bmp";
        saveBMP(rotatedCounterClockwiseFilename, rotatedCounterClockwise);
        std::cout << "Image was rotated counter clockwise and was save " << rotatedCounterClockwiseFilename << "\n";

        BMPImage gaussClockwise = useGaussFilter(rotatedClockwise);
        std::string gaussClockwiseFilename = "gaussClockwise.bmp";
        saveBMP(gaussClockwiseFilename, gaussClockwise);
        std::cout << "Gauss filter is apllied with rotated clockwise image and result is saved " << gaussClockwiseFilename << "\n";

        BMPImage gaussCounterClockwise = useGaussFilter(rotatedCounterClockwise);
        std::string gaussCounterClockwiseFilename = "gaussContercwise.bmp";
        saveBMP(gaussCounterClockwiseFilename, gaussCounterClockwise);
        std::cout << "Gauss filter is apllied with rotated counter clockwise image and result is saved " << gaussCounterClockwiseFilename << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}