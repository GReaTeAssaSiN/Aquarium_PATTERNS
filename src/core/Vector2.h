#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <cmath>

struct Vector2
{
    float x = 0.f;
    float y = 0.f;

    Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
    Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; }
    Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }

    float Length() const { return std::sqrt(x * x + y * y); }

    // Returns a unit-length vector in the same direction, or {0,0} if this is (near) zero-length.
    Vector2 Normalized() const
    {
        const float length = Length();
        if (length < 0.0001f)
            return {0.f, 0.f};
        return {x / length, y / length};
    }
};

#endif // VECTOR2_H_
