#include "bmp.h"
#include "image.h"
#include "gaussfilter.h"
#include <iostream>
#include <string>

int main() {
    try {
        // Загружаем изображение
        std::string inputFilename = "input.bmp";
        BMPImage image;
        image.load(inputFilename);
        std::cout << "Image is uploaded: " << inputFilename << "\n";

        // Поворот по часовой стрелке
        BMPImage rotatedClockwise = rotate90Clockwise(image);
        std::string rotatedClockwiseFilename = "rClockwise.bmp";
        rotatedClockwise.save(rotatedClockwiseFilename);
        std::cout << "Image was rotated clockwise and saved to: " << rotatedClockwiseFilename << "\n";

        // Поворот против часовой стрелки
        BMPImage rotatedCounterClockwise = rotate90CounterClockwise(image);
        std::string rotatedCounterClockwiseFilename = "rCounterClockwise.bmp";
        rotatedCounterClockwise.save(rotatedCounterClockwiseFilename);
        std::cout << "Image was rotated counter clockwise and saved to: " << rotatedCounterClockwiseFilename << "\n";

        // Применение фильтра Гаусса к изображению, повернутому по часовой стрелке
        BMPImage gaussClockwise = useGaussFilter(rotatedClockwise);
        std::string gaussClockwiseFilename = "gaussClockwise.bmp";
        gaussClockwise.save(gaussClockwiseFilename);
        std::cout << "Gauss filter applied to clockwise rotated image and saved to: " << gaussClockwiseFilename << "\n";

        // Применение фильтра Гаусса к изображению, повернутому против часовой стрелки
        BMPImage gaussCounterClockwise = useGaussFilter(rotatedCounterClockwise);
        std::string gaussCounterClockwiseFilename = "gaussCounterClockwise.bmp";
        gaussCounterClockwise.save(gaussCounterClockwiseFilename);
        std::cout << "Gauss filter applied to counter clockwise rotated image and saved to: " << gaussCounterClockwiseFilename << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}