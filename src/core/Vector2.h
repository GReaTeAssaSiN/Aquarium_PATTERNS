#ifndef VECTOR2_H_
#define VECTOR2_H_

struct Vector2
{
    float x = 0.f;
    float y = 0.f;

    Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
    Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; }
    Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
};

#endif // VECTOR2_H_
