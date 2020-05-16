#pragma once

#include <cmath>
#include <inttypes.h>

// credits: csgo_modest
namespace Utils::Math {
  template <typename T> struct Vector2D {
    T x, y;
    Vector2D( ) = default;

    Vector2D( T xy ) : x( xy ), y( xy ){};
    Vector2D( T x, T y ) : x( x ), y( y ){};
    Vector2D( T x, T y, T z ) : x( x ), y( y ){};

    inline constexpr T m_Length( ) { return std::sqrt( x * x + y * y ); }

    inline constexpr bool m_bIsZero( ) { return x == 0 && y == 0; }

    inline Vector2D & operator=( const Vector2D & in ) {
      x = in.x;
      y = in.y;

      return *this;
    }

    inline bool operator!=( const Vector2D & in ) { return ( x != in.x || y != in.y ); }

    inline bool operator==( const Vector2D & in ) { return ( x == in.x && y == in.y ); }

    inline constexpr Vector2D operator+( Vector2D in ) { return Vector2D( x + in.x, y + in.y ); }

    inline constexpr Vector2D operator+( T in ) { return Vector2D( x + in, y + in ); }

    inline Vector2D & operator+=( Vector2D in ) {
      x += in.x;
      y += in.y;

      return *this;
    }

    inline Vector2D & operator+=( T in ) {
      x += in;
      y += in;

      return *this;
    }

    inline constexpr Vector2D operator-( Vector2D in ) { return Vector2D( x - in.x, y - in.y ); }

    inline constexpr Vector2D operator-( T in ) { return Vector2D( x - in, y - in ); }

    inline Vector2D & operator-=( Vector2D in ) {
      x -= in.x;
      y -= in.y;

      return *this;
    }

    inline Vector2D & operator-=( T in ) {
      x -= in;
      y -= in;

      return *this;
    }

    inline constexpr Vector2D operator*( Vector2D in ) { return Vector2D( x * in.x, y * in.y ); }

    inline constexpr Vector2D operator*( T in ) { return Vector2D( x * in, y * in ); }

    inline Vector2D & operator*=( Vector2D in ) {
      x *= in.x;
      y *= in.y;

      return *this;
    }

    inline Vector2D & operator*=( T in ) {
      x *= in;
      y *= in;

      return *this;
    }

    inline constexpr Vector2D operator/( Vector2D in ) { return Vector2D( x / in.x, y / in.y ); }

    inline constexpr Vector2D operator/( T in ) { return Vector2D( x / in, y / in ); }

    inline Vector2D & operator/=( Vector2D in ) {
      x /= in.x;
      y /= in.y;

      return *this;
    }

    inline Vector2D & operator/=( T in ) {
      x /= in;
      y /= in;

      return *this;
    }
  };
  using Vector2 = Vector2D<float>;
} // namespace Utils::Math