#ifndef MATH_GEOMETRY_HPP
#define MATH_GEOMETRY_HPP

#include "matrix.hpp"
#include "point3.hpp"
#include "vec3.hpp"

#include <stdexcept>

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
  [[nodiscard]] constexpr matrix<T> transpose(const matrix<T>& A) noexcept {
    matrix<T> M = A;
    for (int r{}; r < A.rows(); ++r) {
      for (int c{r}; c < A.cols(); ++c) {
        auto temp = M(r, c);
        M(r, c) = M(c, r);
        M(c, r) = temp;
      }
    }
    return M;
  }

  template <typename T>
  [[nodiscard]] constexpr T determinant(const matrix<T>& M);

  template <typename T>
  [[nodiscard]] constexpr matrix<T> submatrix(const matrix<T>& A, int row,
                                              int col);

  template <typename T>
  [[nodiscard]] constexpr T minor(const matrix<T>& A, int row, int col);

  template <typename T>
  [[nodiscard]] constexpr T cofactor(const matrix<T>& A, int row, int col);

  template <typename T> constexpr T determinant(const matrix<T>& M) {
    T det{};

    if (M.rows() == 2) {
      det = M(0, 0) * M(1, 1) - M(1, 0) * M(0, 1);
    } else {
      for (int c{}; c < M.cols(); ++c) {
        det += M(0, c) * cofactor(M, 0, c);
      }
    }

    return det;
  }

  template <typename T>
  constexpr matrix<T> submatrix(const matrix<T>& A, int row, int col) {
    if (A.rows() == 2) {
      throw std::invalid_argument(
          "\nERROR: input matrix must have dimension (3x3) or (4x4)\n"
          "Current matrix dimension is (2x2)");
    }

    matrix<T> M;

    if (A.rows() == 3) {
      M = matrix<T>(2, 2);
    } else {
      M = matrix<T>(3, 3);
    }

    int ret_row{0};
    for (int r{}; r < A.rows(); ++r) {
      int ret_col{0};
      if (r == row) // skip the r^th row
        continue;
      for (int c{}; c < A.cols(); ++c) {
        if (c == col) // skip the c^th column
          continue;
        M(ret_row, ret_col) = A(r, c);
        ret_col += 1;
      }
      ret_row += 1;
    }

    return M;
  }

  template <typename T>
  constexpr T minor(const matrix<T>& A, int row, int col) {
    auto B = submatrix(A, row, col);
    return determinant(B);
  }

  template <typename T>
  constexpr T cofactor(const matrix<T>& A, int row, int col) {
    int sign = ((row + col) & 1) ? -1 : 1; // check parity
    return sign * minor(A, row, col);
  }

  template <typename T>
  [[nodiscard]] constexpr bool is_invertible(const matrix<T>& A) {
    return determinant(A) != 0;
  }

  template <typename T>
  [[nodiscard]] constexpr matrix<T> inverse(const matrix<T>& A) {
    if (!is_invertible(A)) {
      throw std::invalid_argument(
          "\nERROR: trying to find the inverse of a noninvertible matrix");
    }

    matrix<T> M(A.rows(), A.cols());
    auto det_A = determinant(A);

    for (int r{}; r < A.rows(); ++r) {
      for (int c{}; c < A.cols(); ++c) {
        M(c, r) = cofactor(A, r, c) / det_A;
      }
    }

    return M;
  }

  template <typename T>
  [[nodiscard]] constexpr matrix<T> translation(T x, T y, T z) noexcept {
    return matrix<T>({{1.0, 0.0, 0.0, x},
                      {0.0, 1.0, 0.0, y},
                      {0.0, 0.0, 1.0, z},
                      {0.0, 0.0, 0.0, 1.0}});
  }

  template <typename T>
  [[nodiscard]] constexpr matrix<T> scaling(T x, T y, T z) noexcept {
    return matrix<T>({{x, 0.0, 0.0, 0.0},
                      {0.0, y, 0.0, 0.0},
                      {0.0, 0.0, z, 0.0},
                      {0.0, 0.0, 0.0, 1.0}});
  }

  template <typename T>
  [[nodiscard]] constexpr matrix<T> rotation_x(T theta) noexcept {
    // | 1.0    0.0         0.0     0.0 |
    // | 0.0 cos(theta) -sin(theta) 0.0 |
    // | 0.0 sin(theta)  cos(theta) 0.0 |
    // | 0.0    0.0         0.0     1.0 |
    return matrix<T>({{1.0, 0.0, 0.0, 0.0},
                      {0.0, std::cos(theta), -std::sin(theta), 0.0},
                      {0.0, std::sin(theta), std::cos(theta), 0.0},
                      {0.0, 0.0, 0.0, 1.0}});
  }

  template <typename T>
  [[nodiscard]] constexpr matrix<T> rotation_y(T theta) noexcept {
    // | cos(theta) 0.0  -sin(theta)  0.0 |
    // |    0.0     1.0     0.0       0.0 |
    // | sin(theta) 0.0   cos(theta)  0.0 |
    // |    0.0     0.0     0.0       1.0 |
    return matrix<T>({{std::cos(theta), 0.0, std::sin(theta), 0.0},
                      {0.0, 1.0, 0.0, 0.0},
                      {-std::sin(theta), 0.0, std::cos(theta), 0.0},
                      {0.0, 0.0, 0.0, 1.0}});
  }

  template <typename T>
  [[nodiscard]] constexpr matrix<T> rotation_z(T theta) noexcept {
    // | cos(theta)    -sin(theta)    0.0     0.0 |
    // | sin(theta)     cos(theta)    0.0     0.0 |
    // |    0.0             0.0       1.0     0.0 |
    // |    0.0             0.0       0.0     1.0 |
    return matrix<T>({{std::cos(theta), -std::sin(theta), 0.0, 0.0},
                      {std::sin(theta), std::cos(theta), 0.0, 0.0},
                      {0.0, 0.0, 1.0, 0.0},
                      {0.0, 0.0, 0.0, 1.0}});
  }

  template <typename T>
  [[nodiscard]] constexpr matrix<T>
  shearing(T x_prop_y = 0.0, T x_prop_z = 0.0, T y_prop_x = 0.0,
           T y_prop_z = 0.0, T z_prop_x = 0.0, T z_prop_y = 0.0) noexcept {
    return matrix<T>({{1.0, x_prop_y, x_prop_z, 0.0},
                      {y_prop_x, 1.0, y_prop_z, 0.0},
                      {z_prop_x, z_prop_y, 1.0, 0.0},
                      {0.0, 0.0, 0.0, 1.0}});
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

  template <typename T>
  [[nodiscard]] constexpr matrix<T> operator*(const matrix<T>& A,
                                              const matrix<T>& B) {
    if (A.rows() != B.rows() || A.cols() != B.cols()) {
      throw std::invalid_argument(
          std::format("\nERROR: trying to multiply unequal matrices\ndims(LHS) "
                      "= ({}, {})\tdims(RHS) = ({}, {})",
                      A.rows(), A.cols(), B.rows(), B.cols()));
    }

    const auto rows = A.rows();
    const auto cols = B.cols();

    matrix<T> M(rows, cols);

    for (int r{}; r < rows; ++r) {
      for (int c{}; c < cols; ++c) {
        auto cur_sum = 0.0;
        for (int k{}; k < A.cols(); ++k) { // A.cols == B.rows
          cur_sum += A(r, k) * B(k, c);
        }
        M(r, c) = cur_sum;
      }
    }

    return M;
  };

  template <typename T>
  [[nodiscard]] constexpr container<T> operator*(const matrix<T>& A,
                                                 const container<T>& x) {

    const auto rows = A.rows();
    const auto cols = A.cols();

    if (cols != x.size()) {
      throw std::invalid_argument(
          std::format("\nERROR: trying to multiply a matrix and container with "
                      "unequal dimensions\ndims(MATRIX) "
                      "= ({}, {})\tdims(CONTAINER) = ({}, 1)",
                      rows, cols, x.size()));
    }

    container<T> b{};

    for (int r{}; r < rows; ++r) {
      auto sum = 0.0;
      for (int c{}; c < cols; ++c) {
        sum += A(r, c) * x[c];
      }
      b[r] = sum;
    }

    return b;
  }

  template <typename T>
  [[nodiscard]] constexpr point3<T> operator*(const matrix<T>& A,
                                              const point3<T>& p) {
    container<T> res = A * static_cast<container<T>>(p);
    return point3<T>(res.x(), res.y(), res.z());
  }
} // namespace math

#endif // !MATH_GEOMETRY_HPP
