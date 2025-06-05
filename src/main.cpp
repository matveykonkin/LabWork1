/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#include <chrono>
#include <iostream>
#include "image.h"
#include "turnimage.h"

/**
 * @brief Точка входа в программу. Запрашивает у пользователя параметры, выполняет повороты и размытие изображений, выводит время выполнения операций.
 * @param argc Количество аргументов командной строки
 * @param argv Аргументы командной строки
 * @return Код завершения
 */
int main(int argc, char* argv[])
{
    std::cout << "Enter path to image file, radius (int), and sigma (float) for Gaussian blur:" << std::endl;
    
    std::string path;
    std::getline(std::cin, path);
    
    int radius;
    float sigma;
    std::cin >> radius >> sigma;

    auto start = std::chrono::high_resolution_clock::now();
    Turn_Image::RightTurn(path.c_str());
    auto end = std::chrono::high_resolution_clock::now();
    auto rightTurnTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    Turn_Image::LeftTurn(path.c_str());
    end = std::chrono::high_resolution_clock::now();
    auto leftTurnTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    Image leftImage(0, 0);
    leftImage.Read("Left_rotated_image.bmp");
    
    start = std::chrono::high_resolution_clock::now();
    leftImage.ApplyGaussianBlur(radius, sigma);
    end = std::chrono::high_resolution_clock::now();
    auto leftBlurTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    leftImage.Export("Blurred_Left_Rotated_Image.bmp");

    Image rightImage(0, 0);
    rightImage.Read("Right_rotated_image.bmp");
    
    start = std::chrono::high_resolution_clock::now();
    rightImage.ApplyGaussianBlur(radius, sigma);
    end = std::chrono::high_resolution_clock::now();
    auto rightBlurTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    rightImage.Export("Blurred_Right_Rotated_Image.bmp");

    std::cout << "\nPerformance results (ms):\n"
              << "Right turn: " << rightTurnTime.count() << "\n"
              << "Left turn: " << leftTurnTime.count() << "\n"
              << "Left blur: " << leftBlurTime.count() << "\n"
              << "Right blur: " << rightBlurTime.count() << std::endl;

    return 0;
}