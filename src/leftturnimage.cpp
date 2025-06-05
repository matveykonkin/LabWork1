/* ## LabWork1
## Author
Konkin Matvey B83-mm
## Contacts
st135668@student.spbu.ru
## Description
LabWork1 */

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include "image.h"
#include "turnimage.h"

void Turn_Image::LeftTurn(const char* path) {
    Image image(0, 0);
    image.Read(path);
    int height = image.GetHeight();
    int width = image.GetWidth();
    Image rotatedImage(height, width);

    unsigned numThreads = std::min(8u, std::thread::hardware_concurrency());
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    auto worker = [&](int startY, int endY) {
        for (int y = startY; y < endY; ++y) {
            for (int x = 0; x < width; ++x) {
                rotatedImage.SetColor(image.GetColor(x, y), y, width - x - 1);
            }
        }
    };

    int rowsPerThread = height / numThreads;
    int remainingRows = height % numThreads;
    int startY = 0;

    for (unsigned i = 0; i < numThreads; ++i) {
        int endY = startY + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.emplace_back(worker, startY, endY);
        startY = endY;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    rotatedImage.Export("Left_rotated_image.bmp");
}