/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#include <iostream>
#include <vector>
#include <string>
#include "image.h"
#include "turnimage.h"

int main(int argc, char* argv[])
{
    std::cout << "Enter path to image file, radius (int), and sigma (float) for Gaussian blur:" << std::endl;
    
    std::string path;
    std::getline(std::cin, path);
    
    int radius;
    float sigma;
    std::cin >> radius >> sigma;

    Turn_Image::RightTurn(path.c_str());
    Turn_Image::LeftTurn(path.c_str());

    Image leftImage(0, 0);
    leftImage.Read("Left_rotated_image.bmp");
    leftImage.ApplyGaussianBlur(radius, sigma);
    leftImage.Export("Blurred_Left_Rotated_Image.bmp");

    Image rightImage(0, 0);
    rightImage.Read("Right_rotated_image.bmp");
    rightImage.ApplyGaussianBlur(radius, sigma);
    rightImage.Export("Blurred_Right_Rotated_Image.bmp");

    return 0;
}