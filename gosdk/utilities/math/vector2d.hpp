#pragma once

#include <inttypes.h>
#include <cmath>

// credits: csgo_modest
namespace utilities::math
{
template <typename T> struct vec2 {
	T x, y;
	vec2() = default;

	vec2(T xy) : x(xy), y(xy){};
	vec2(T x, T y) : x(x), y(y){};
	vec2(T x, T y, T z) : x(x), y(y){};

	inline constexpr T length()
	{
		return std::sqrt(x * x + y * y);
	}

	inline constexpr bool is_zero()
	{
		return x == 0 && y == 0;
	}

	inline vec2 &operator=(const vec2 &in)
	{
		x = in.x;
		y = in.y;

		return *this;
	}

	inline bool operator!=(const vec2 &in)
	{
		return (x != in.x || y != in.y);
	}

	inline bool operator==(const vec2 &in)
	{
		return (x == in.x && y == in.y);
	}

	inline constexpr vec2 operator+(vec2 in)
	{
		return vec2_t(x + in.x, y + in.y);
	}

	inline constexpr vec2 operator+(T in)
	{
		return vec2_t(x + in, y + in);
	}

	inline vec2 &operator+=(vec2 in)
	{
		x += in.x;
		y += in.y;

		return *this;
	}

	inline vec2 &operator+=(T in)
	{
		x += in;
		y += in;

		return *this;
	}

	inline constexpr vec2 operator-(vec2 in)
	{
		return vec2(x - in.x, y - in.y);
	}

	inline constexpr vec2 operator-(T in)
	{
		return vec2(x - in, y - in);
	}

	inline vec2 &operator-=(vec2 in)
	{
		x -= in.x;
		y -= in.y;

		return *this;
	}

	inline vec2 &operator-=(T in)
	{
		x -= in;
		y -= in;

		return *this;
	}

	inline constexpr vec2 operator*(vec2 in)
	{
		return vec2(x * in.x, y * in.y);
	}

	inline constexpr vec2 operator*(T in)
	{
		return vec2(x * in, y * in);
	}

	inline vec2 &operator*=(vec2 in)
	{
		x *= in.x;
		y *= in.y;

		return *this;
	}

	inline vec2 &operator*=(T in)
	{
		x *= in;
		y *= in;

		return *this;
	}

	inline constexpr vec2 operator/(vec2 in)
	{
		return vec2(x / in.x, y / in.y);
	}

	inline constexpr vec2 operator/(T in)
	{
		return vec2(x / in, y / in);
	}

	inline vec2 &operator/=(vec2 in)
	{
		x /= in.x;
		y /= in.y;

		return *this;
	}

	inline vec2 &operator/=(T in)
	{
		x /= in;
		y /= in;

		return *this;
	}
};
using vec2_t = vec2<float>;
} // namespace utilities::math