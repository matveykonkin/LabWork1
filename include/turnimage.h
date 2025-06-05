/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#ifndef TURNIMAGE_H
#define TURNIMAGE_H

/**
 * @namespace Turn_Image
 * @brief Пространство имён для функций поворота изображения.
 */
namespace Turn_Image
{
    /**
     * @brief Поворачивает изображение на 90 градусов вправо и сохраняет результат.
     * @param path Путь к исходному изображению
     */
    void RightTurn(const char* path);
    /**
     * @brief Поворачивает изображение на 90 градусов влево и сохраняет результат.
     * @param path Путь к исходному изображению
     */
    void LeftTurn(const char* path);
}

#endif