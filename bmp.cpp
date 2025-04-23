#include "bmp.h"
#include <fstream>
#include <iostream>

bool readBMP(const std::string& filename, BMPHeader& bmpHeader, DIBHeader& dibHeader, std::vector<std::vector<Pixel>>& pixels) {
    std::ifstream file(filename, std::ios::binary);
    if(!file) {
        std::cerr << "Can't open file: " << filename << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    file.read(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));

    if(bmpHeader.signature[0] != 'B' || bmpHeader.signature[1] != 'M') {
        std::cerr << "Not a valid BMP file!" << std::endl;
        return false;
    }

    file.seekg(bmpHeader.data0ffset, std::ios::beg);

    int width = dibHeader.width;
    int height = dibHeader.height;
    int rowSize = (width * 3 + 3) & (~3);

    pixels.resize(height, std::vector<Pixel>(width));

    for(int y = height - 1; y >= 0; --y) {
        file.read(reinterpret_cast<char*>(pixels[y].data()), width * sizeof(Pixel));
        file.ignore(rowSize - width * sizeof(Pixel));
    }

    return true;
}

bool writeBMP(const std::string& filename, const BMPHeader& bmpHeader, const DIBHeader& dibHeader, const std::vector<std::vector<Pixel>>& pixels) {
    std::ofstream file(filename, std::ios::binary);
    if(!file) {
        std::cerr << "Can't write to file: " << filename << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
    file.write(reinterpret_cast<const char*>(&dibHeader), sizeof(dibHeader));

    int width = dibHeader.width;
    int height = dibHeader.height;
    int rowSize = (width * 3 + 3) & (~3);
    std::vector<uint8_t> padding(rowSize - width * sizeof(Pixel), 0);

    for(int y = height - 1; y >= 0; --y) {
        file.write(reinterpret_cast<const char*>(pixels[y].data()), width * sizeof(Pixel));
        file.write(reinterpret_cast<const char*>(padding.data()), padding.size());
    }

    return true;
}

void rotate90(std::vector<std::vector<Pixel>>& pixels) {
    int h = pixels.size();
    int w = pixels[0].size();
    std::vector<std::vector<Pixel>> rotated(w, std::vector<Pixel>(h));
    for(int y = 0; y < h; ++y)
        for(int x = 0; x < w; ++x)
            rotated[x][h - y -1] = pixels[y][x];
    pixels = rotated;
}
