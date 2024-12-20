/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#ifndef KERNEL_H
#define KERNEL_H

#include <vector>

namespace Gauss_Kernel
{
    std::vector<std::vector<float>> GenerateGaussianKernel(int radius, float sigma);
}

#endif