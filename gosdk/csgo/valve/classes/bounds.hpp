#pragma once

#include "../../../utilities/math/global.hpp"

// inb4 UC screams at me
#pragma warning( disable : 4244 )

namespace CS::Classes {
  class Box {
  public:
    int m_iX, m_iY, m_iW, m_iH;

    Box( ) = default;
    ~Box( ) = default;

    Box( int x, int y, int w, int h ) : m_iX( x ), m_iY( y ), m_iW( w ), m_iH( h ) {}
    Box( const Utils::Math::Vector2 & tl, const Utils::Math::Vector2 & br )
        : m_iX( tl.m_X ), m_iY( tl.m_Y ), m_iW( br.m_X - tl.m_X ), m_iH( tl.m_Y - br.m_Y ) {}

    Box( const Box & ) = default;
    Box & operator=( Box & ) = default;

    /* Don't make RValues const! [The compiler won't let you anyway] */
    Box( Box && ) = default;
    Box & operator=( Box && ) = default;

    constexpr int m_iRight( ) const { return m_iX + m_iW; }

    constexpr int m_iBottom( ) const { return m_iY + m_iH; }

    constexpr bool m_bIsInBounds( const Utils::Math::Vector2 & pt ) const {
      if ( this->m_iX > pt.m_X )
        return false;
      if ( this->m_iY > pt.m_Y )
        return false;
      if ( this->m_iRight( ) < pt.m_X )
        return false;
      if ( this->m_iBottom( ) < pt.m_Y )
        return false;

      return true;
    }
  };
} // namespace CS::Classes