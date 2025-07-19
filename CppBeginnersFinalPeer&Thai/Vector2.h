#pragma once
#include <functional> // For std::hash

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

    // Equality operator
    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }
};

// Hash specialization for Vector2<T>
namespace std 
{
    template <typename T>
    struct hash<Vector2<T>>
    {
        std::size_t operator()(const Vector2<T>& v) const
        {
            return std::hash<T>()(v.x) ^ (std::hash<T>()(v.y) << 1);
        }
    };
}