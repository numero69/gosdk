#pragma once

template <typename T> class CUtlVector {
public:
  constexpr T & operator[]( int i ) noexcept { return m_Memory[ i ]; };

  T * m_Memory;
  int m_iAllocationCount;
  int m_GrowSize;
  int m_iSize;
  T * m_Elements;
};