/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#pragma once

#include <iostream>
#include <vector>
#include "kernel.h"

/**
 * @struct Color
 * @brief Представляет цвет пикселя в формате RGB с плавающей точкой.
 */
struct Color
{
    float r, g, b; ///< Компоненты цвета (красный, зелёный, синий)
    /**
     * @brief Конструктор по умолчанию. Устанавливает цвет в чёрный.
     */
    Color();
    /**
     * @brief Конструктор с параметрами.
     * @param r Красная компонента
     * @param g Зелёная компонента
     * @param b Синяя компонента
     */
    Color(float r, float g, float b);
    /**
     * @brief Деструктор.
     */
    ~Color();
};

#pragma pack(push, 1)
/**
 * @struct BMPFileHeader
 * @brief Заголовок BMP-файла (основная информация о файле).
 */
struct BMPFileHeader
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

/**
 * @struct BMPInfoHeader
 * @brief Информация о BMP-изображении (размеры, глубина цвета и т.д.).
 */
struct BMPInfoHeader
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xpelsPerMeter;
    int32_t ypelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};
#pragma pack(pop)

/**
 * @class Image
 * @brief Класс для работы с изображениями: чтение, сохранение, размытие, доступ к пикселям.
 */
class Image
{
public:
    /**
     * @brief Конструктор изображения.
     * @param width Ширина изображения
     * @param height Высота изображения
     */
    Image(int width, int height);
    /**
     * @brief Деструктор.
     */
    ~Image();
    /**
     * @brief Получить ширину изображения.
     * @return Ширина
     */
    int GetWidth() const;
    /**
     * @brief Получить высоту изображения.
     * @return Высота
     */
    int GetHeight() const;
    /**
     * @brief Получить цвет пикселя по координатам.
     * @param x X-координата
     * @param y Y-координата
     * @return Цвет пикселя
     */
    Color GetColor(int x, int y) const;
    /**
     * @brief Установить цвет пикселя по координатам.
     * @param color Новый цвет
     * @param x X-координата
     * @param y Y-координата
     */
    void SetColor(const Color& color, int x, int y);
    /**
     * @brief Прочитать изображение из BMP-файла.
     * @param path Путь к файлу
     */
    void Read(const char* path);
    /**
     * @brief Сохранить изображение в BMP-файл.
     * @param path Путь к файлу
     */
    void Export(const char* path) const;
    /**
     * @brief Применить гауссово размытие к изображению.
     * @param radius Радиус ядра
     * @param sigma Сигма (стандартное отклонение)
     */
    void ApplyGaussianBlur(int radius, float sigma);
    /**
     * @brief Вспомогательный потоковый обработчик для размытия.
     * @param startY Начальная строка
     * @param endY Конечная строка
     * @param kernel Ядро размытия
     * @param radius Радиус ядра
     * @param blurredImage Ссылка на изображение для записи результата
     */
    void ParallelBlurWorker(int startY, int endY, const std::vector<std::vector<float>>& kernel, int radius, Image& blurredImage);

private:
    int m_width;
    int m_height;
    std::vector<Color> m_pixels;
};