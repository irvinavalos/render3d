#ifndef MATH_MATRIX_HPP
#define MATH_MATRIX_HPP

#include <format>
#include <stdexcept>
#include <vector>

#include "utils.hpp"

namespace math {
  template <typename T>
    requires decimal<T>
  class matrix {
  public:
    constexpr matrix() noexcept = default;

    constexpr explicit matrix(int num_rows, int num_cols) {
      if ((num_rows == 4 && num_cols == 4) ||
          (num_rows == 3 && num_cols == 3) ||
          (num_rows == 2 && num_cols == 2)) {
        m_size = num_rows * num_cols;
        m_rows = num_rows;
        m_cols = num_cols;
        m_items = std::vector<T>(m_size);
      } else {
        throw std::invalid_argument(
            std::format("\nERROR: matrix must be one of\n(1) 2x2\n(2) 3x3\n(3) "
                        "4x4\nCurrent number of rows and columns = ({}, {})",
                        num_rows, num_cols));
      }
    }

    constexpr explicit matrix(
        std::initializer_list<std::initializer_list<T>> data) {
      auto data_size = data.size();
      if (data_size == 4 || data_size == 3 || data_size == 2) {
        m_size = data_size * data_size;
        m_rows = data_size;
        m_cols = data_size;
        m_items = std::vector<T>(m_size);
      } else {
        throw std::invalid_argument(
            std::format("\nERROR: matrix must be one of\n(1) 2x2\n(2) 3x3\n(3) "
                        "4x4\nCurrent number of rows in data = {}",
                        data_size));
      }

      auto r = 0;
      for (auto& row : data) {
        if (r >= m_rows) {
          throw std::invalid_argument(std::format(
              "\nERROR: matrix must consist of {} rows\nCurrent number "
              "of rows in data = {}",
              data_size, r));
        }
        auto c = 0;
        for (auto& val : row) {
          if (c >= m_cols) {
            throw std::invalid_argument(std::format(
                "\nERROR: matrix must consist of {} columns\nCurrent "
                "number of columns in data = {}",
                data_size, c));
          }
          m_items[r * m_cols + c++] = val;
        }
        r += 1;
      }
    }

    constexpr void transpose() noexcept {
      for (int r{}; r < m_rows; ++r) {
        for (int c{r}; c < m_cols; ++c) {
          auto temp = (*this)(r, c);
          (*this)(r, c) = (*this)(c, r);
          (*this)(c, r) = temp;
        }
      }
    }

    [[nodiscard]] constexpr int rows() const noexcept { return m_rows; }
    [[nodiscard]] constexpr int cols() const noexcept { return m_cols; }

    [[nodiscard]] constexpr T at(int i, int j) const {
      return m_items.at(index_of(i, j, m_cols));
    }

    [[nodiscard]] constexpr T operator()(int i, int j) const noexcept {
      return m_items[index_of(i, j, m_cols)];
    }

    [[nodiscard]] constexpr T& operator()(int i, int j) noexcept {
      return m_items[index_of(i, j, m_cols)];
    }

    [[nodiscard]] constexpr bool
    operator==(const matrix& other) const noexcept {
      if (m_size != other.m_size) // implicitly compares rows and cols
        return false;

      for (int i{}; i < m_size; ++i) {
        if (!math::equal_floats(m_items.at(i), other.m_items.at(i)))
          return false;
      }

      return true;
    }

  private:
    int m_size{};
    int m_rows{};
    int m_cols{};

    std::vector<T> m_items{};

    [[nodiscard]] static inline int index_of(int i, int j, int ncols) noexcept {
      return i * ncols + j;
    }
  };
} // namespace math

#endif // !MATH_MATRIX_HPP
