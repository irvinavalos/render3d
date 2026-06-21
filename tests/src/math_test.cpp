#include <cmath>

#include <doctest.h>
#include <math/geometry.hpp>

TEST_CASE("container with w=1.0 is a point") {
  math::container c(1.0, 2.0, 3.0, 1.0);

  CHECK_EQ(c.is_point(), true);
  CHECK_EQ(c.is_vector(), false);
}

TEST_CASE("container with w=0.0 is a vector") {
  math::container c(1.0, 2.0, 3.0, 0.0);

  CHECK_EQ(c.is_point(), false);
  CHECK_EQ(c.is_vector(), true);
}

TEST_CASE("point3() creates a container with w=1.0") {
  math::point3 p(1.0, 2.0, 3.0);

  CHECK_EQ(p, math::container(1.0, 2.0, 3.0, 1.0));
}

TEST_CASE("vec3() creates a container with w=0.0") {
  math::vec3 v(1.0, 2.0, 3.0);

  CHECK_EQ(v, math::container(1.0, 2.0, 3.0, 0.0));
}

TEST_CASE("adding two vectors") {
  math::vec3 v1(1.0, 2.0, 3.0);
  math::vec3 v2(-1.0, 2.0, -3.0);

  CHECK_EQ(v1 + v2, math::container(0.0, 4.0, 0.0, 0.0));
}

TEST_CASE("adding a point and vector") {
  math::point3 p(1.1, 1.2, 1.3);
  math::vec3 v(-0.1, -0.2, -0.3);

  CHECK_EQ(p + v, math::container(1.0, 1.0, 1.0, 1.0));
  CHECK_EQ(v + p, math::point3(1.0, 1.0, 1.0));
}

TEST_CASE("subtracting two points") {
  math::point3 p1(1.0, 2.0, 3.0);
  math::point3 p2(1.0, 2.0, 3.0);

  CHECK_EQ(p1 - p2, math::vec3(0.0, 0.0, 0.0));

  // check that point - point should be vector not point
  CHECK(p1 - p2 != math::point3(0.0, 0.0, 0.0));
}

TEST_CASE("negating a vector") {
  math::vec3 v(1.0, -2.0, 3.0);

  CHECK_EQ(-v, math::vec3(-1.0, 2.0, -3.0));
}

TEST_CASE("subtracting two vectors") {
  math::vec3 v1(2.1, 2.3, 2.6);
  math::vec3 v2(2.3, -2.5, 2.7);

  CHECK_EQ(v1 - v2, math::vec3(-0.2, 4.8, -0.1));
}

TEST_CASE("subtracting a vector from a point") {
  math::point3 p(1.0, 2.0, 3.0);
  math::vec3 v(1.0, -2.0, 3.0);

  CHECK_EQ(p - v, math::point3(0.0, 4.0, 0.0));
}

TEST_CASE("multipying a point/vector by a scalar") {
  math::point3 p(1.0, -2.0, 3.0);
  math::vec3 v(-1.0, 2.0, -3.0);

  double a{3.5};

  CHECK_EQ(p * a, math::point3(3.5, -7.0, 10.5));
  CHECK_EQ(a * v, math::vec3(-3.5, 7.0, -10.5));
}

TEST_CASE("multipying a point/vector by a fraction") {
  math::point3 p(1.0, -2.0, 3.0);
  math::vec3 v(-1.0, 2.0, -3.0);

  double a{0.5};

  CHECK_EQ(p * a, math::point3(0.5, -1.0, 1.5));
  CHECK_EQ(a * v, math::vec3(-0.5, 1.0, -1.5));
}

TEST_CASE("dividing a point/vector by a scalar") {
  math::point3 p(1.0, -2.0, 3.0);
  math::vec3 v(-1.0, 2.0, -3.0);

  double a{2};

  CHECK_EQ(p / a, math::point3(0.5, -1.0, 1.5));
  CHECK_EQ(v / a, math::vec3(-0.5, 1.0, -1.5));
}

TEST_CASE("computing the magnitude of a vector") {
  math::vec3 e0(1.0, 0.0, 0.0);
  math::vec3 e1(0.0, 1.0, 0.0);
  math::vec3 e2(0.0, 0.0, 1.0);

  CHECK_EQ(e0.length(), 1.0);
  CHECK_EQ(e1.length(), 1.0);
  CHECK_EQ(e2.length(), 1.0);

  math::vec3 v1(1.0, 2.0, 3.0);
  math::vec3 v2(-1.0, -2.0, -3.0);

  CHECK_EQ(v1.length(), std::sqrt(14.0));
  CHECK_EQ(v2.length(), std::sqrt(14.0));
}

TEST_CASE("normalizing a vector") {
  math::vec3 v1(9.0, 0.0, 0.0);
  auto v1_norm = math::normalize(v1);

  CHECK_EQ(v1_norm, math::vec3(1.0, 0.0, 0.0));

  math::vec3 v2(1.0, 2.0, 3.0);
  auto v2_norm = math::normalize(v2);

  CHECK_EQ(v2_norm, math::vec3(1.0 / std::sqrt(14), 2.0 / std::sqrt(14),
                               3.0 / std::sqrt(14)));

  CHECK_EQ(v2_norm.length(), 1.0);
}

TEST_CASE("dot product of two vectors") {
  math::vec3 v1(1.0, 2.0, 3.0);
  math::vec3 v2(2.0, 3.0, 4.0);

  CHECK_EQ(math::dot(v1, v2), 20.0);
}

TEST_CASE("cross product of two vectors") {
  math::vec3 v1(1.0, 2.0, 3.0);
  math::vec3 v2(2.0, 3.0, 4.0);

  CHECK_EQ(math::cross(v1, v2), math::vec3(-1.0, 2.0, -1.0));
  CHECK_EQ(math::cross(v2, v1), math::vec3(1.0, -2.0, 1.0));
}
