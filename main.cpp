#include <iostream>
#include "bmp.h"

int main() {
    BMPHeader bmpHeader;
    DIBHeader dibHeader;
    std::vector<std::vector<Pixel>> pixels;

    if(!readBMP("input.bmp", bmpHeader, dibHeader, pixels)) {
         return 1;
    }

    rotate90(pixels);

    std::swap(dibHeader.width, dibHeader.height);

    writeBMP("rotated.bmp", bmpHeader, dibHeader, pixels);
    std::cout << "Rotation done!" << std::endl;
    return 0;
}
