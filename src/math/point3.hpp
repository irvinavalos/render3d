#ifndef MATH_POINT3_HPP
#define MATH_POINT3_HPP

#include "container.hpp"

namespace math {
  template <typename T> class point3 : public container<T> {
  public:
    point3() = default;
    constexpr explicit point3(T x, T y, T z) noexcept
        : container<T>(x, y, z, 1.0) {}

    constexpr point3& operator*=(T scalar) noexcept {
      (*this)[index::x] *= scalar;
      (*this)[index::y] *= scalar;
      (*this)[index::z] *= scalar;

      return *this;
    }

    constexpr point3& operator/=(T scalar) noexcept {
      (*this) *= (1.0 / scalar);
      return *this;
    }
  };

} // namespace math

#endif // !MATH_POINT3_HPP
