#ifndef MATH_VEC3_HPP
#define MATH_VEC3_HPP

#include "container.hpp"

namespace math {
  template <typename T> class vec3 : public container<T> {
  public:
    vec3() = default;
    constexpr explicit vec3(T x, T y, T z) noexcept
        : container<T>(x, y, z, 0.0) {}

    [[nodiscard]] constexpr T length() const noexcept {
      auto x2 = this->x() * this->x();
      auto y2 = this->y() * this->y();
      auto z2 = this->z() * this->z();

      return sqrt_float(x2 + y2 + z2);
    }

    constexpr vec3& operator+=(const vec3& rhs) noexcept {
      (*this)[index::x] += rhs[index::x];
      (*this)[index::y] += rhs[index::y];
      (*this)[index::z] += rhs[index::z];

      return *this;
    }

    [[nodiscard]] constexpr vec3 operator-() const noexcept {
      return vec3(-this->x(), -this->y(), -this->z());
    }

    constexpr vec3& operator-=(const vec3& rhs) noexcept {
      (*this) += (-rhs);
      return *this;
    }

    constexpr vec3& operator*=(T scalar) noexcept {
      (*this)[index::x] *= scalar;
      (*this)[index::y] *= scalar;
      (*this)[index::z] *= scalar;

      return *this;
    }

    constexpr vec3& operator/=(T scalar) noexcept {
      (*this) *= (1.0 / scalar);
      return *this;
    }
  };

} // namespace math

#endif // !MATH_VEC3_HPP
