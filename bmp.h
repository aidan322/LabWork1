#ifndef BMP_H
#define BMP_H

#include <string>
#include <vector>

#pragma pack(push, 1)
struct BMPHeader {
    char signature[2];
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t data0ffset;
};

struct DIBHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};
#pragma pack(pop)

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

bool readBMP(const std::string& filename, BMPHeader& bmpHeader, DIBHeader& dibHeader, std::vector<std::vector<Pixel>>& pixels);
bool writeBMP(const std::string& filename, const BMPHeader& bmpHeader, const DIBHeader& dibHeader, const std::vector<std::vector<Pixel>>& pixels);
void rotate90Clockwise(std::vector<std::vector<Pixel>>& pixels);
void rotate90CounterClockwise(std::vector<std::vector<Pixel>>& pixels);

#endif
