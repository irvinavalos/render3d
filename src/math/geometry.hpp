#ifndef MATH_GEOMETRY_HPP
#define MATH_GEOMETRY_HPP

#include "point3.hpp"
#include "vec3.hpp"

namespace math {
  template <typename T>
  [[nodiscard]] constexpr vec3<T> normalize(const vec3<T>& v) noexcept {
    auto magnitude = v.length();
    return vec3(v.x() / magnitude, v.y() / magnitude, v.z() / magnitude);
  }

  template <typename T>
  [[nodiscard]] constexpr T dot(const vec3<T>& v1, const vec3<T>& v2) noexcept {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
  }

  template <typename T>
  [[nodiscard]] constexpr vec3<T> cross(const vec3<T>& v1,
                                        const vec3<T>& v2) noexcept {
    auto x_hat = v1.y() * v2.z() - v1.z() * v2.y();
    auto y_hat = v1.z() * v2.x() - v1.x() * v2.z();
    auto z_hat = v1.x() * v2.y() - v1.y() * v2.x();
    return vec3(x_hat, y_hat, z_hat);
  }

  template <typename T>
  [[nodiscard]] constexpr vec3<T> operator-(const point3<T>& p1,
                                            const point3<T>& p2) noexcept {
    return vec3(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
  }

  template <typename T>
  [[nodiscard]] constexpr vec3<T> operator+(vec3<T> v1,
                                            const vec3<T>& v2) noexcept {
    v1 += v2;
    return v1;
  }

  template <typename T>
  [[nodiscard]] constexpr vec3<T> operator-(vec3<T> v1,
                                            const vec3<T>& v2) noexcept {
    v1 -= v2;
    return v1;
  }

  template <typename T>
  [[nodiscard]] constexpr point3<T> operator+(const point3<T>& p,
                                              const vec3<T>& v) noexcept {
    return point3(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
  }

  template <typename T>
  [[nodiscard]] constexpr point3<T> operator+(const vec3<T>& v,
                                              const point3<T>& p) noexcept {
    return p + v;
  }

  template <typename T>
  [[nodiscard]] constexpr point3<T> operator-(const point3<T>& p,
                                              const vec3<T>& v) noexcept {
    return p + (-v);
  }

  template <typename T>
  [[nodiscard]] constexpr vec3<T> operator*(vec3<T> v, T scalar) noexcept {
    v *= scalar;
    return v;
  }

  template <typename T>
  [[nodiscard]] constexpr vec3<T> operator*(T scalar,
                                            const vec3<T>& v) noexcept {
    return v * scalar;
  }

  template <typename T>
  [[nodiscard]] constexpr point3<T> operator*(point3<T> p, T scalar) noexcept {
    p *= scalar;
    return p;
  }

  template <typename T>
  [[nodiscard]] constexpr point3<T> operator*(T scalar,
                                              const point3<T>& p) noexcept {
    return p * scalar;
  }

  template <typename T>
  [[nodiscard]] constexpr vec3<T> operator/(const vec3<T>& v,
                                            T scalar) noexcept {
    return v * (1.0 / scalar);
  }

  template <typename T>
  [[nodiscard]] constexpr point3<T> operator/(const point3<T>& p,
                                              T scalar) noexcept {
    return p * (1.0 / scalar);
  }
} // namespace math

#endif // !MATH_GEOMETRY_HPP
