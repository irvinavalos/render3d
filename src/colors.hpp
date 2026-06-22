#ifndef COLORS_HPP
#define COLORS_HPP

#include "math/container.hpp"

namespace render3d {
  enum index : int { red = 0, green = 1, blue = 2 };

  template <typename T> class color : public math::container<T> {
  public:
    constexpr explicit color(T red, T green, T blue) noexcept
        : math::container<T>(red, green, blue, 1.0) {}

    [[nodiscard]] constexpr T x() const noexcept = delete;
    [[nodiscard]] constexpr T y() const noexcept = delete;
    [[nodiscard]] constexpr T z() const noexcept = delete;
    [[nodiscard]] constexpr T w() const noexcept = delete;

    [[nodiscard]] constexpr T red() const noexcept {
      return (*this)[index::red];
    }

    [[nodiscard]] constexpr T green() const noexcept {
      return (*this)[index::green];
    }

    [[nodiscard]] constexpr T blue() const noexcept {
      return (*this)[index::blue];
    }

    constexpr color& operator+=(const color& rhs) noexcept {
      (*this)[index::red] += rhs[index::red];
      (*this)[index::green] += rhs[index::green];
      (*this)[index::blue] += rhs[index::blue];

      return *this;
    }

    [[nodiscard]] constexpr color operator-() const noexcept {
      return color(-this->red(), -this->green(), -this->blue());
    }

    constexpr color& operator-=(const color& rhs) noexcept {
      (*this) += (-rhs);
      return *this;
    }

    [[nodiscard]] friend constexpr color operator+(color c1,
                                                   const color& c2) noexcept {
      c1 += c2;
      return c1;
    }

    [[nodiscard]] friend constexpr color operator-(color c1,
                                                   const color& c2) noexcept {
      c1 -= c2;
      return c1;
    }

    // uses haddamard product
    constexpr color& operator*=(const color& c) noexcept {
      (*this)[index::red] *= c.red();
      (*this)[index::green] *= c.green();
      (*this)[index::blue] *= c.blue();

      return *this;
    }

    [[nodiscard]] friend constexpr color operator*(color c1,
                                                   const color& c2) noexcept {
      c1 *= c2;
      return c1;
    }

    constexpr color& operator*=(T scalar) noexcept {
      (*this)[index::red] *= scalar;
      (*this)[index::green] *= scalar;
      (*this)[index::blue] *= scalar;

      return *this;
    }

    [[nodiscard]] friend constexpr color operator*(color c, T scalar) noexcept {
      c *= scalar;
      return c;
    }

    [[nodiscard]] friend constexpr color operator*(T scalar, color c) noexcept {
      return c * scalar;
    }
  };

} // namespace render3d

#endif // !COLORS_HPP
