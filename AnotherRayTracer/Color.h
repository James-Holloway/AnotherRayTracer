#pragma once
#include <algorithm>

struct Color
{
    Color(double _r = 0, double _g = 0, double _b = 0);

    double r = 0.0f;
    double g = 0.0f;
    double b = 0.0f;

    Color operator+(Color other) const;
    Color operator-(Color other) const;
    Color operator*(Color other) const;
    Color operator*(double scalar) const;
    Color operator/(Color other) const;
    Color operator/(double scalar) const;

    void ToBytes(unsigned char& red, unsigned char& green, unsigned char& blue) const;
};

const Color CBlack = Color(0, 0, 0);
const Color CWhite = Color(1, 1, 1);
const Color CCornflowerBlue = Color(0.392, 0.584, 0.929);