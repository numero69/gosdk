#pragma once

#include <inttypes.h>
#include <cmath>

// credits: csgo_modest
namespace utilities::math
{
template <typename T> struct vec3 {
	T x, y, z;

	vec3() = default;

	vec3(T xyz) : x(xyz), y(xyz), z(xyz){};
	vec3(T x, T y) : x(x), y(y), z(0){};
	vec3(T x, T y, T z) : x(x), y(y), z(z){};

	inline constexpr T length()
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	inline constexpr T length_2d()
	{
		T root = 0.0f;

		T sqst = x * x + y * y;

		__asm
		{
				sqrtss xmm0, sqst
				movss root, xmm0
		}

		return root;
	}

	inline constexpr vec3 normalize()
	{
		vec3 out{};
		T l = length();

		if (l != 0) {
			out.x = x / l;
			out.y = y / l;
			out.z = z / l;
		} else
			out.x = out.y = 0.0f;
		out.z = 1.0f;

		return out;
	}

	inline constexpr T self_dot()
	{
		return (x * x + y * y + z * z);
	}

	inline constexpr T dot(const vec3 &in)
	{
		return (x * in.x + y * in.y + z * in.z);
	}

	inline vec3 &operator=(const vec3 &in)
	{
		x = in.x;
		y = in.y;
		z = in.z;

		return *this;
	}

	inline bool operator!=(const vec3 &in)
	{
		return (x != in.x || y != in.y || z != in.z);
	}

	inline bool operator==(const vec3 &in)
	{
		return (x == in.x && y == in.y && z == in.z);
	}

	inline constexpr vec3 operator+(vec3 in)
	{
		return vec3(x + in.x, y + in.y, z + in.z);
	}

	inline constexpr vec3 operator+(T in)
	{
		return vec3(x + in, y + in, z + in);
	}

	inline vec3 &operator+=(vec3 in)
	{
		x += in.x;
		y += in.y;
		z += in.z;

		return *this;
	}

	inline vec3 &operator+=(T in)
	{
		x += in;
		y += in;
		z += in;

		return *this;
	}

	inline constexpr vec3 operator-(vec3 in)
	{
		return vec3(x - in.x, y - in.y, z - in.z);
	}

	inline constexpr vec3 operator-(T in)
	{
		return vec3(x - in, y - in, z - in);
	}

	inline vec3 &operator-=(vec3 in)
	{
		x -= in.x;
		y -= in.y;
		z -= in.z;

		return *this;
	}

	inline vec3 &operator-=(T in)
	{
		x -= in;
		y -= in;
		z -= in;

		return *this;
	}

	inline constexpr vec3 operator*(vec3 in)
	{
		return vec3(x * in.x, y * in.y, z * in.z);
	}

	inline constexpr vec3 operator*(T in)
	{
		return vec3(x * in, y * in, z * in);
	}

	inline vec3 &operator*=(vec3 in)
	{
		x *= in.x;
		y *= in.y;
		z *= in.z;

		return *this;
	}

	inline vec3 &operator*=(T in)
	{
		x *= in;
		y *= in;
		z *= in;

		return *this;
	}

	inline constexpr vec3 operator/(vec3 in)
	{
		return vec3(x / in.x, y / in.y, z / in.z);
	}

	inline constexpr vec3 operator/(T in)
	{
		return vec3(x / in, y / in, z / in);
	}

	inline vec3 &operator/=(vec3 in)
	{
		x /= in.x;
		y /= in.y;
		z /= in.z;

		return *this;
	}

	inline vec3 &operator/=(T in)
	{
		x /= in;
		y /= in;
		z /= in;

		return *this;
	}
};
using vec3_t = vec3<float>;
} // namespace utilities::math