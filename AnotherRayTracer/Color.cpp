#include "Color.h"

Color::Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

Color Color::operator+(Color other) const
{
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator-(Color other) const
{
    return Color(r - other.r, g - other.g, b - other.b);
}

Color Color::operator*(Color other) const
{
    return Color(r * other.r, g * other.g, b * other.b);
}

Color Color::operator*(double scalar) const
{
    return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator/(Color other) const
{
    return Color(r / other.r, g / other.g, b / other.b);
}

Color Color::operator/(double scalar) const
{
    return Color(r / scalar, g / scalar, b / scalar);
}

void Color::ToBytes(unsigned char& red, unsigned char& green, unsigned char& blue) const
{
    red = (unsigned char)(r * 255);
    green = (unsigned char)(g * 255);
    blue = (unsigned char)(b * 255);
}
