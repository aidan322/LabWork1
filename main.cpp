#include <iostream>
#include "bmp.h"

int main() {
    BMPHeader bmpHeader;
    DIBHeader dibHeader;
    std::vector<std::vector<Pixel>> pixels;

    if(!readBMP("input.bmp", bmpHeader, dibHeader, pixels)) {
         return 1;
    }

    std::cout << "Choose rotation:\n";
    std::cout << "1 - Clockwise (по часовой)\n";
    std::cout << "2 - Counter-clockwise (против часовой)\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        rotate90Clockwise(pixels);
    } else if (choice == 2) {
        rotate90CounterClockwise(pixels);
    } else {
        std::cerr << "Invalid choice!\n";
        return 1;
    }

    std::swap(dibHeader.width, dibHeader.height);

    if(!writeBMP("rotated.bmp", bmpHeader, dibHeader, pixels)) {
        return 1;
    }

    std::cout << "Rotation done!" << std::endl;
    return 0;
}
