#include <doctest.h>

#include <math/geometry.hpp>

TEST_CASE("constructing and inspecting a 4x4 matrix") {
  math::matrix mat({{1.0, 2.0, 3.0, 4.0},
                    {5.5, 6.5, 7.5, 8.5},
                    {9.0, 10.0, 11.0, 12.0},
                    {13.5, 14.5, 15.5, 16.5}});

  CHECK_EQ(mat(0, 0), 1.0);
  CHECK_EQ(mat(0, 3), 4.0);
  CHECK_EQ(mat(1, 0), 5.5);
  CHECK_EQ(mat(1, 2), 7.5);
  CHECK_EQ(mat(2, 2), 11.0);
  CHECK_EQ(mat(3, 0), 13.5);
  CHECK_EQ(mat(3, 2), 15.5);
}

TEST_CASE("constructing and inspecting a 2x2 matrix") {
  math::matrix mat({{-3.0, 5.0}, {1.0, -2.0}});

  CHECK_EQ(mat(0, 0), -3.0);
  CHECK_EQ(mat(0, 1), 5.0);
  CHECK_EQ(mat(1, 0), 1.0);
  CHECK_EQ(mat(1, 1), -2.0);
}

TEST_CASE("constructing and inspecting a 3x3 matrix") {
  math::matrix mat({{-3.0, 5.0, 0.0}, {1.0, -2.0, -7.0}, {0.0, 1.0, 1.0}});

  CHECK_EQ(mat(0, 0), -3.0);
  CHECK_EQ(mat(1, 1), -2.0);
  CHECK_EQ(mat(2, 2), 1.0);
}

TEST_CASE("matrix equality with identical matrices") {
  math::matrix A({
      {1.0, 2.0, 3.0, 4.0},
      {5.0, 6.0, 7.0, 8.0},
      {9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, 16.0},
  });

  math::matrix B({
      {1.0, 2.0, 3.0, 4.0},
      {5.0, 6.0, 7.0, 8.0},
      {9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, 16.0},
  });

  CHECK_EQ(A, B);
}

TEST_CASE("matrix equality with different matrices") {
  math::matrix A({
      {1.0, 2.0, 3.0, 4.0},
      {5.0, 6.0, 7.0, 8.0},
      {9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, 16.0},
  });

  math::matrix B({
      {1.0, 2.0, 3.0, 4.0},
      {5.0, 6.0, 7.0, 8.0},
      {9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, -16.0},
  });

  CHECK(A != B);
}

TEST_CASE("multiplying two matrices") {
  math::matrix A({
      {1.0, 2.0, 3.0, 4.0},
      {5.0, 6.0, 7.0, 8.0},
      {9.0, 8.0, 7.0, 6.0},
      {5.0, 4.0, 3.0, 2.0},
  });

  math::matrix B({
      {-2.0, 1.0, 2.0, 3.0},
      {3.0, 2.0, 1.0, -1.0},
      {4.0, 3.0, 6.0, 5.0},
      {1.0, 2.0, 7.0, 8.0},
  });

  math::matrix C({{20.0, 22.0, 50.0, 48.0},
                  {44.0, 54.0, 114.0, 108.0},
                  {40.0, 58.0, 110.0, 102.0},
                  {16.0, 26.0, 46.0, 42.0}});

  CHECK_EQ(A * B, C);
}

TEST_CASE("a matrix multiplied by a container") {
  math::matrix A({
      {1.0, 2.0, 3.0, 4.0},
      {2.0, 4.0, 4.0, 2.0},
      {8.0, 6.0, 4.0, 1.0},
      {0.0, 0.0, 0.0, 1.0},
  });

  math::container x(1.0, 2.0, 3.0, 1.0);

  CHECK_EQ(A * x, math::container(18.0, 24.0, 33.0, 1.0));
}

TEST_CASE("multiplying a matrix by the identity matrix") {
  math::matrix A({
      {1.0, 2.0, 3.0, 4.0},
      {1.0, 2.0, 4.0, 8.0},
      {2.0, 4.0, 8.0, 16.0},
      {4.0, 8.0, 16.0, 32.0},
  });

  CHECK_EQ(A * math::ident_matrix<double>(4), A);
}

TEST_CASE("multiplying the identity matrix by a container") {
  math::container c(1.0, 2.0, 3.0, 4.0);

  CHECK_EQ(math::ident_matrix<double>(4) * c, c);
}

TEST_CASE("transposing a matrix") {
  math::matrix A({
      {0.0, 9.0, 3.0, 0.0},
      {9.0, 8.0, 0.0, 8.0},
      {1.0, 8.0, 5.0, 3.0},
      {0.0, 0.0, 5.0, 8.0},
  });

  auto A_original = A;

  A.transpose();

  CHECK_EQ(math::transpose(A_original), A);
  CHECK_EQ(A, math::matrix({
                  {0.0, 9.0, 1.0, 0.0},
                  {9.0, 8.0, 8.0, 0.0},
                  {3.0, 0.0, 5.0, 5.0},
                  {0.0, 8.0, 3.0, 8.0},
              }));
}

TEST_CASE("transposing the identity matrix") {
  math::matrix I = math::matrix<double>(4, 4);

  I.transpose();

  CHECK_EQ(I, math::matrix<double>(4, 4));
}

TEST_CASE("determinant of a 2x2 matrix") {
  math::matrix A({{1.0, 5.0}, {-3.0, 2.0}});

  CHECK_EQ(math::determinant(A), 17);
}

TEST_CASE("a submatrix of a (3x3) matrix is a (2x2)") {
  math::matrix A({{1.0, -2.0, 3.0}, {-4.0, 5.0, -6.0}, {7.0, -8.0, 9.0}});

  CHECK_EQ(math::submatrix(A, 0, 2), math::matrix({{-4.0, 5.0}, {7.0, -8.0}}));
}

TEST_CASE("a submatrix of a (4x4) matrix is a (3x3)") {
  math::matrix A({{1.0, -2.0, 3.0, -4.0},
                  {-5.0, 6.0, -7.0, 8.0},
                  {9.0, -10.0, 11.0, -12.0},
                  {-13.0, 14.0, -15.0, 16.0}});

  CHECK_EQ(math::submatrix(A, 2, 1),
           math::matrix(
               {{1.0, 3.0, -4.0}, {-5.0, -7.0, 8.0}, {-13.0, -15.0, 16.0}}));
}

TEST_CASE("computing the minor of a (3x3) matrix") {
  math::matrix A({
      {3.0, 5.0, 0.0},
      {2.0, -1.0, -7.0},
      {6.0, -1.0, 5.0},
  });

  auto B = math::submatrix(A, 1, 0);

  CHECK_EQ(math::determinant(B), math::minor(A, 1, 0));
}

TEST_CASE("computing the cofactor of a (3x3) matrix") {
  math::matrix A({
      {3.0, 5.0, 0.0},
      {2.0, -1.0, -7.0},
      {6.0, -1.0, 5.0},
  });

  CHECK(math::minor(A, 0, 0) == math::cofactor(A, 0, 0));
  CHECK(math::minor(A, 1, 0) != math::cofactor(A, 1, 0));
}

TEST_CASE("computing the determinant of a (3x3) matrix") {
  math::matrix A({
      {1.0, 2.0, 6.0},
      {-5.0, 8.0, -4.0},
      {2.0, 6.0, 4.0},
  });

  CHECK_EQ(math::cofactor(A, 0, 0), 56);
  CHECK_EQ(math::cofactor(A, 0, 1), 12);
  CHECK_EQ(math::cofactor(A, 0, 2), -46);
  CHECK_EQ(math::determinant(A), -196);
}

TEST_CASE("computing the determinant of a (4x4) matrix") {
  math::matrix A({{-2.0, -8.0, 3.0, 5.0},
                  {-3.0, 1.0, 7.0, 3.0},
                  {1.0, 2.0, -9.0, 6.0},
                  {-6.0, 7.0, 7.0, -9.0}});

  CHECK_EQ(math::cofactor(A, 0, 0), 690);
  CHECK_EQ(math::cofactor(A, 0, 1), 447);
  CHECK_EQ(math::cofactor(A, 0, 2), 210);
  CHECK_EQ(math::cofactor(A, 0, 3), 51);
  CHECK_EQ(math::determinant(A), -4071);
}

TEST_CASE("testing the invertibility of a (4x4) matrix") {
  math::matrix A({{6.0, 4.0, 4.0, 4.0},
                  {5.0, 5.0, 7.0, 6.0},
                  {4.0, -9.0, 3.0, -7.0},
                  {9.0, 1.0, 7.0, -6.0}});

  CHECK(math::determinant(A) != 0); // one way to check for invertbility
  CHECK_EQ(math::is_invertible(A), true);
}

TEST_CASE("testing the non-invertibility of a (4x4) matrix") {
  math::matrix A({{-4.0, 2.0, -2.0, -3.0},
                  {9.0, 6.0, 2.0, 6.0},
                  {0.0, -5.0, 1.0, -5.0},
                  {0.0, 0.0, 0.0, 0.0}});

  CHECK(math::determinant(A) == 0);
  CHECK_EQ(math::is_invertible(A), false);
}

TEST_CASE("computing the inverse of a (4x4) matrix") {
  math::matrix A1({{-5.0, 2.0, 6.0, -8.0},
                   {1.0, -5.0, 1.0, 8.0},
                   {7.0, 7.0, -6.0, -7.0},
                   {1.0, -3.0, 7.0, 4.0}});

  CHECK(math::inverse(A1) ==
        math::matrix<double>({{0.21805, 0.45113, 0.24060, -0.04511},
                              {-0.80827, -1.45677, -0.44361, 0.52068},
                              {-0.07895, -0.22368, -0.05263, 0.19737},
                              {-0.52256, -0.81391, -0.30075, 0.30639}}));

  math::matrix A2({{8.0, -5.0, 9.0, 2.0},
                   {7.0, 5.0, 6.0, 1.0},
                   {-6.0, 0.0, 9.0, 6.0},
                   {-3.0, 0.0, -9.0, -4.0}});

  CHECK(math::inverse(A2) ==
        math::matrix<double>({{-0.15385, -0.15385, -0.28205, -0.53846},
                              {-0.07692, 0.12308, 0.02564, 0.03077},
                              {0.35897, 0.35897, 0.43590, 0.92308},
                              {-0.69231, -0.69231, -0.76923, -1.92308}}));

  math::matrix A3({{9.0, 3.0, 0.0, 9.0},
                   {-5.0, -2.0, -6.0, -3.0},
                   {-4.0, 9.0, 6.0, 4.0},
                   {-7.0, 6.0, 6.0, 2.0}});

  CHECK(math::inverse(A3) ==
        math::matrix<double>({{-0.04074, -0.07778, 0.14444, -0.22222},
                              {-0.07778, 0.03333, 0.36667, -0.33333},
                              {-0.02901, -0.14630, -0.10926, 0.12963},
                              {0.17778, 0.06667, -0.26667, 0.33333}}));
}

TEST_CASE("multiplying a matrix product by its inverse") {
  math::matrix A({{3.0, -9.0, 7.0, 3.0},
                  {3.0, -8.0, 2.0, -9.0},
                  {-4.0, 4.0, 4.0, 1.0},
                  {-6.0, 5.0, -1.0, 1.0}});

  math::matrix B({{8.0, 2.0, 2.0, 2.0},
                  {3.0, -1.0, 7.0, 0.0},
                  {7.0, 0.0, 5.0, 4.0},
                  {5.0, -2.0, 0.0, 5.0}});

  auto C = A * B;

  CHECK_EQ(C * math::inverse(B), A);
  CHECK_EQ(math::inverse(A) * C, B);
}

TEST_CASE("inverting the identity matrix") {
  auto I = math::ident_matrix<double>(4);

  CHECK_EQ(math::inverse(I), I);
}

TEST_CASE("multiplying a matrix by its inverse") {
  math::matrix<double> A(
      {{-1.0, 2.0, -3.0}, {4.0, -5.0, 6.0}, {7.0, 8.0, 9.0}});

  CHECK_EQ(A * math::inverse(A), math::ident_matrix<double>(3));
}

TEST_CASE("inverse of the transpose of a matrix") {
  math::matrix<double> A(
      {{1.0, -2.0, 3.0}, {-4.0, -5.0, -6.0}, {7.0, 8.0, 9.0}});

  CHECK_EQ(math::inverse(math::transpose(A)),
           math::transpose(math::inverse(A)));
}

TEST_CASE("scaling a container via the identity matrix") {
  auto I = math::ident_matrix<double>(4);
  I(2, 2) = 3.1;

  math::container x(1.0, 1.0, 1.0, 1.0);

  CHECK_EQ(I * x, math::container(1.0, 1.0, 3.1, 1.0));
}
