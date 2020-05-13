#pragma once

#include <cmath>
#include <inttypes.h>

// credits: csgo_modest
namespace Utils::Math {
  template <typename T> struct Vector3 {
    T x, y, z;

    Vector3( ) = default;

    Vector3( T xyz ) : x( xyz ), y( xyz ), z( xyz ){};
    Vector3( T x, T y ) : x( x ), y( y ), z( 0 ){};
    Vector3( T x, T y, T z ) : x( x ), y( y ), z( z ){};

    inline constexpr T Length( ) { return std::sqrt( x * x + y * y + z * z ); }

    inline constexpr T Length2D( ) {
      T root = 0.0f;

      T sqst = x * x + y * y;

      __asm
      {
				sqrtss xmm0, sqst
				movss root, xmm0
      }

      return root;
    }

    inline constexpr Vector3 Normalize( ) {
      Vector3 out{};
      T l = Length( );

      if ( l != 0 ) {
        out.x = x / l;
        out.y = y / l;
        out.z = z / l;
      } else
        out.x = out.y = 0.0f;
      out.z = 1.0f;

      return out;
    }

    inline constexpr T SelfDot( ) { return ( x * x + y * y + z * z ); }

    inline constexpr T Dot( const Vector3 & in ) { return ( x * in.x + y * in.y + z * in.z ); }

    inline Vector3 & operator=( const Vector3 & in ) {
      x = in.x;
      y = in.y;
      z = in.z;

      return *this;
    }

    inline bool operator!=( const Vector3 & in ) { return ( x != in.x || y != in.y || z != in.z ); }

    inline bool operator==( const Vector3 & in ) { return ( x == in.x && y == in.y && z == in.z ); }

    inline constexpr Vector3 operator+( Vector3 in ) { return Vector3( x + in.x, y + in.y, z + in.z ); }

    inline constexpr Vector3 operator+( T in ) { return Vector3( x + in, y + in, z + in ); }

    inline Vector3 & operator+=( Vector3 in ) {
      x += in.x;
      y += in.y;
      z += in.z;

      return *this;
    }

    inline Vector3 & operator+=( T in ) {
      x += in;
      y += in;
      z += in;

      return *this;
    }

    inline constexpr Vector3 operator-( Vector3 in ) { return Vector3( x - in.x, y - in.y, z - in.z ); }

    inline constexpr Vector3 operator-( T in ) { return Vector3( x - in, y - in, z - in ); }

    inline Vector3 & operator-=( Vector3 in ) {
      x -= in.x;
      y -= in.y;
      z -= in.z;

      return *this;
    }

    inline Vector3 & operator-=( T in ) {
      x -= in;
      y -= in;
      z -= in;

      return *this;
    }

    inline constexpr Vector3 operator*( Vector3 in ) { return Vector3( x * in.x, y * in.y, z * in.z ); }

    inline constexpr Vector3 operator*( T in ) { return Vector3( x * in, y * in, z * in ); }

    inline Vector3 & operator*=( Vector3 in ) {
      x *= in.x;
      y *= in.y;
      z *= in.z;

      return *this;
    }

    inline Vector3 & operator*=( T in ) {
      x *= in;
      y *= in;
      z *= in;

      return *this;
    }

    inline constexpr Vector3 operator/( Vector3 in ) { return Vector3( x / in.x, y / in.y, z / in.z ); }

    inline constexpr Vector3 operator/( T in ) { return Vector3( x / in, y / in, z / in ); }

    inline Vector3 & operator/=( Vector3 in ) {
      x /= in.x;
      y /= in.y;
      z /= in.z;

      return *this;
    }

    inline Vector3 & operator/=( T in ) {
      x /= in;
      y /= in;
      z /= in;

      return *this;
    }
  };
  using Vector = Vector3<float>;
} // namespace Utils::Math