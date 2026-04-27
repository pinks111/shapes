#pragma once 
#include <fstream>
#include <cstdint>
#include "Matrix.h"
#include "Storage.h"

class Bitmap {
  Matrix<bool> matrix_;
public:
  Bitmap(size_t r, size_t c): matrix_(r, c) {}

  bool Get(size_t r, size_t c);

  void Set(size_t r, size_t c, bool state) {
    matrix_.set(r, c, state);
  }

  void Save(const char* filename) {
    std::ofstream f(filename, std::ios::binary);
    if (!f) return false;

    int rowSize = ((matrix_.width() + 31) / 32) * 4;
    int imageSize = rowSize * matrix_.height();

    // --- FILE HEADER ---
    uint16_t bfType = 0x4D42;
    uint32_t bfOffBits = 14 + 40 + 8;
    uint32_t bfSize = bfOffBits + imageSize;
    uint16_t zero = 0;

    f.write((char*)&bfType, 2);
    f.write((char*)&bfSize, 4);
    f.write((char*)&zero, 2);
    f.write((char*)&zero, 2);
    f.write((char*)&bfOffBits, 4);

    // --- INFO HEADER ---
    uint32_t biSize = 40;
    int32_t biWidth = matrix_.width();
    int32_t biHeight = matrix_.height();
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 1;
    uint32_t biCompression = 0;
    uint32_t biSizeImage = imageSize;
    int32_t ppm = 2835;
    uint32_t clrUsed = 2;

    f.write((char*)&biSize, 4);
    f.write((char*)&biWidth, 4);
    f.write((char*)&biHeight, 4);
    f.write((char*)&biPlanes, 2);
    f.write((char*)&biBitCount, 2);
    f.write((char*)&biCompression, 4);
    f.write((char*)&biSizeImage, 4);
    f.write((char*)&ppm, 4);
    f.write((char*)&ppm, 4);
    f.write((char*)&clrUsed, 4);
    f.write((char*)&clrUsed, 4);

    // --- PALETTE ---
    uint8_t palette[8] = {
        0,0,0,0,
        255,255,255,0
    };
    f.write((char*)palette, 8);

    // --- PIXELS ---
    bool* row = new bool[rowSize];

    for (int y = height - 1; y >= 0; y--) {
        std::fill(row, row+(rowSize-1), 0);

        for (int x = 0; x < width; x++) {
            if (data.get(y,x)) {
                row[x / 8] |= (1 << (7 - (x % 8)));
            }
        }

        f.write((char*)row, rowSize);
    }
    delete[] row;

    return true;
  }

  static Bitmap load(const char *filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open file");

    uint16_t bfType;
    f.read((char*)&bfType, 2);
    if (bfType != 0x4D42) throw std::runtime_error("Not BMP");

    f.ignore(8);
    uint32_t bfOffBits;
    f.read((char*)&bfOffBits, 4);

    uint32_t biSize;
    f.read((char*)&biSize, 4);

    int32_t width, height;
    f.read((char*)&width, 4);
    f.read((char*)&height, 4);

    uint16_t planes, bitCount;
    f.read((char*)&planes, 2);
    f.read((char*)&bitCount, 2);

    if (bitCount != 1) throw std::runtime_error("Not 1-bit BMP");

    f.ignore(bfOffBits - 14 - 16);

    Bitmap img(width, height);

    int rowSize = ((width + 31) / 32) * 4;
    bool * row = new bool[RowSize];

    for (int y = height - 1; y >= 0; y--) {
        f.read((char*)row, rowSize);

        for (int x = 0; x < width; x++) {
            int bit = (row[x / 8] >> (7 - (x % 8))) & 1;
            img.set(x, y, bit);
        }
    }
    delete[] row;

    return img;
  }

};
