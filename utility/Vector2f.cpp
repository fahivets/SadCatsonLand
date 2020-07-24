#include "stdafx.h"
#include "Vector2f.h"

// Constructors/Destructors

constexpr Vector2f::Vector2f(float xValue, float yValue) : x(xValue), y(yValue)
{}

constexpr Vector2f::Vector2f(const Vector2f & rVec) : x(rVec.x), y(rVec.y)
{}

float Vector2f::magnitudeSqrt() const
{
    return (x * x + y * y);
}

float Vector2f::magnitude() const
{
    return (static_cast<float>(sqrt(magnitudeSqrt())));
}

Vector2f Vector2f::normalize()
{
    float mag = magnitude();
    return (Vector2f(x / mag, y / mag));
}

Vector2f& Vector2f::operator+=(const Vector2f& rVec)
{
    x += rVec.x;
    y += rVec.y;
    return (*this);
}

Vector2f& Vector2f::operator-=(const Vector2f& rVec)
{
    x -= rVec.x;
    y -= rVec.y;
    return (*this);
}

Vector2f& Vector2f::operator*=(const Vector2f& rVec)
{
    x *= rVec.x;
    y *= rVec.y;
    return (*this);
}

Vector2f& Vector2f::operator/=(const Vector2f& rVec)
{
    x /= rVec.x;
    y /= rVec.y;
    return (*this);
}

Vector2f operator+(Vector2f& rVec1, const Vector2f& rVec2)
{
    rVec1 += rVec2;
    return (rVec1);
}

Vector2f operator-(Vector2f& rVec1, const Vector2f& rVec2)
{
    rVec1 -= rVec2;
    return (rVec1);
}

Vector2f operator*(Vector2f& rVec1, const Vector2f& rVec2)
{
    rVec1 *= rVec2;
    return (rVec1);
}

Vector2f operator/(Vector2f& rVec1, const Vector2f& rVec2)
{
    rVec1 /= rVec2;
    return (rVec1);
}

std::ostream& operator<<(std::ostream& out, const Vector2f& vec)
{
    out << "(" << vec.x << ", " << vec.y << ")";
    return (out);
}

//////TESTTTTT
Vector2f& Vector2f::operator+=(const float& rVal)
{
    x += rVal;
    y += rVal;
    return (*this);
}

Vector2f& Vector2f::operator-=(const float& rVal)
{
    x -= rVal;
    y -= rVal;
    return (*this);
}

Vector2f& Vector2f::operator*=(const float& rVal)
{
    x *= rVal;
    y *= rVal;
    return (*this);
}

Vector2f& Vector2f::operator/=(const float& rVal)
{
    x /= rVal;
    y /= rVal;
    return (*this);
}

Vector2f operator+(Vector2f& rVec1, const float& rVal)
{
    rVec1 += rVal;
    return (rVec1);
}

Vector2f operator-(Vector2f& rVec1, const float& rVal)
{
    rVec1 -= rVal;
    return (rVec1);
}

Vector2f operator*(Vector2f& rVec1, const float& rVal)
{
    rVec1 *= rVal;
    return (rVec1);
}

Vector2f operator/(Vector2f& rVec1, const float& rVal)
{
    rVec1 /= rVal;
    return (rVec1);
}