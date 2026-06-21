#ifndef MATH_CONTAINER_HPP
#define MATH_CONTAINER_HPP

#include <array>

#include "utils.hpp"

namespace math {
  enum index : int { x = 0, y = 1, z = 2, w = 3 };

  template <typename T>
    requires decimal<T>
  class container {
  public:
    constexpr container() noexcept = default;
    constexpr explicit container(T x, T y, T z, T w) noexcept
        : m_items{x, y, z, w} {}

    [[nodiscard]] constexpr bool is_vector() const noexcept {
      return m_items[index::w] == 0.0;
    }

    [[nodiscard]] constexpr bool is_point() const noexcept {
      return !(is_vector());
    }

    [[nodiscard]] constexpr T x() const noexcept { return m_items[index::x]; }
    [[nodiscard]] constexpr T y() const noexcept { return m_items[index::y]; }
    [[nodiscard]] constexpr T z() const noexcept { return m_items[index::z]; }
    [[nodiscard]] constexpr T w() const noexcept { return m_items[index::w]; }

    [[nodiscard]] constexpr T operator[](int i) const noexcept {
      return m_items[i];
    }

    [[nodiscard]] constexpr T& operator[](int i) noexcept { return m_items[i]; }

    [[nodiscard]] constexpr bool
    operator==(const container& rhs) const noexcept {
      return (equal_floats(x(), rhs.x()) && equal_floats(y(), rhs.y()) &&
              equal_floats(z(), rhs.z()) && equal_floats(w(), rhs.w()));
    }

  private:
    std::array<T, 4> m_items;
  };

} // namespace math

#endif // !MATH_CONTAINER_HPP
