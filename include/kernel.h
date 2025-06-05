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

/**
 * @namespace Gauss_Kernel
 * @brief Пространство имён для функций генерации гауссова ядра.
 */
namespace Gauss_Kernel
{
    /**
     * @brief Генерирует двумерное гауссово ядро для размытия изображения.
     * @param radius Радиус ядра
     * @param sigma Сигма (стандартное отклонение)
     * @return Двумерный вектор с коэффициентами ядра
     */
    std::vector<std::vector<float>> GenerateGaussianKernel(int radius, float sigma);
}

#endif