#pragma once
#include <functional>
#include <type_traits>

// Template class with numeric type restriction
template <typename T>
struct Vector2Impl
{
	static_assert(std::is_arithmetic_v<T>, "Vector2Impl requires a numeric type");

	T x, y;

	Vector2Impl(T x_, T y_) : x(x_), y(y_) {}

	void Randomize(int maxValue)
	{
		x = rand() % (maxValue + 1);
		y = rand() % (maxValue + 1);

		++x;
		++y;
	}

	Vector2Impl operator+(const Vector2Impl& other) const
	{
		return Vector2Impl(x + other.x, y + other.y);
	}

	Vector2Impl operator-(const Vector2Impl& other) const
	{
		return Vector2Impl(x - other.x, y - other.y);
	}

	bool operator==(const Vector2Impl& other) const
	{
		return x == other.x && y == other.y;
	}

	Vector2Impl& operator+=(const Vector2Impl& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2Impl& operator-=(const Vector2Impl& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
};

// Type alias to default to int
using Vector2 = Vector2Impl<int>;

// Hash specialization for Vector2Impl<T>
namespace std
{
	template <typename T>
	struct hash<Vector2Impl<T>>
	{
		static_assert(std::is_arithmetic_v<T>, "Hash requires a numeric type for Vector2Impl");
		std::size_t operator()(const Vector2Impl<T>& v) const
		{
			return std::hash<T>()(v.x) ^ (std::hash<T>()(v.y) << 1);
		}
	};
}