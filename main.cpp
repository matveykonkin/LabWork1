#include "bmp.h"
#include "image.h"
#include "gaussfilter.h"
#include <iostream>
#include <string>

int main() {
	try {
		std::string inputFilename = "input.bmp";
		BMPImage image;
		image.load(inputFilename);
		std::cout << "Image loaded: " << inputFilename << "\n";

		BMPImage rotatedClockwise = rotate90Clockwise(image);
		std::string rotatedClockwiseFilename = "rClockwise.bmp";
		rotatedClockwise.save(rotatedClockwiseFilename);
		std::cout << "Image rotated clockwise and saved to: " << rotatedClockwiseFilename << "\n";

		BMPImage rotatedCounterClockwise = rotate90CounterClockwise(image);
		std::string rotatedCounterClockwiseFilename = "rCounterClockwise.bmp";
		rotatedCounterClockwise.save(rotatedCounterClockwiseFilename);
		std::cout << "Image rotated counterclockwise and saved to: " << rotatedCounterClockwiseFilename << "\n";

        int gaussCoreSize = 5;  
        double gaussSigma = 1.5; 

        BMPImage gaussClockwise = useGaussFilter(rotatedClockwise, gaussCoreSize, gaussSigma);
        std::string gaussClockwiseFilename = "gaussClockwise.bmp";
        gaussClockwise.save(gaussClockwiseFilename);
        std::cout << "Gauss filter applied to clockwise rotated image and saved to: " << gaussClockwiseFilename << "\n";

        BMPImage gaussCounterClockwise= useGaussFilter(rotatedCounterClockwise, gaussCoreSize, gaussSigma);
        std::string gaussCounterClockwiseFilename= "gaussCounterClockwise.bmp";
        gaussCounterClockwise.save(gaussCounterClockwiseFilename);
        std::cout << "Gauss filter applied to counterclockwise rotated image and saved to: " << gaussCounterClockwiseFilename << "\n";

	} catch (const std::exception& e) {
	    std::cerr << "Error: " << e.what() << "\n";
	    return 1;
	}

	return 0;
}