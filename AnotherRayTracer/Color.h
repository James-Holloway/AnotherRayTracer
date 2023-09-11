#pragma once
struct Color
{
    Color(float _r = 0, float _g = 0, float _b = 0);

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

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