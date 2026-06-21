#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <cmath>
#include <concepts>

namespace math {
  template <typename T>
  concept decimal = std::floating_point<T>;

  template <decimal T>
  [[nodiscard]] constexpr bool equal_floats(T a, T b) noexcept {
    return (std::fabs(a - b) < 0.00001);
  }

  template <decimal T> [[nodiscard]] constexpr T sqrt_float(T a) noexcept {
    return std::sqrt(a);
  }
} // namespace math

#endif // !MATH_UTILS_HPP
