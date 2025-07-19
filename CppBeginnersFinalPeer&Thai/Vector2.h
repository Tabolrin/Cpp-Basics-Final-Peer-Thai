#pragma once
template <typename T>
struct Vector2
{
    T x, y;

    Vector2(T x_, T y_) : x(x_), y(y_) {}

    void Randomize(int maxValue)
    {
        x = rand() % (maxValue + 1);
        y = rand() % (maxValue + 1);

        ++x;
        ++y;
    }


    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }


    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
};