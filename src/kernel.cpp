/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#include <cmath>
#include <vector>
#include <algorithm>
#include "kernel.h"

std::vector<std::vector<float>> Gauss_Kernel::GenerateGaussianKernel(int radius, float sigma)
{
    int size = 2 * radius + 1;
    std::vector<std::vector<float>> kernel(size, std::vector<float>(size));
    float sum = 0.0f;

    for (int y = -radius; y <= radius; ++y)
    {
        for (int x = -radius; x <= radius; ++x)
        {
            float exponent = -(x * x + y * y) / (2 * sigma * sigma);
            kernel[y + radius][x + radius] = std::exp(exponent) / (2 * M_PI * sigma * sigma);
            sum += kernel[y + radius][x + radius];
        }
    }

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            kernel[y][x] /= sum;
        }
    }

    return kernel;
}