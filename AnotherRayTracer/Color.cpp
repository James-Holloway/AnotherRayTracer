#include "Color.h"

Color::Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}

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
    red = (unsigned char)(std::clamp(r, 0.0, 1.0) * 255);
    green = (unsigned char)(std::clamp(g, 0.0, 1.0) * 255);
    blue = (unsigned char)(std::clamp(b, 0.0, 1.0) * 255);
}
