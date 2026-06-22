#include <colors.hpp>
#include <doctest.h>

TEST_CASE("colors are (red, green, blue) containers") {
  render3d::color c(0.5, 0.4, 1.7);

  CHECK_EQ(c.red(), 0.5);
  CHECK_EQ(c.green(), 0.4);
  CHECK_EQ(c.blue(), 1.7);
}

TEST_CASE("adding colors") {
  render3d::color c1(0.9, 0.6, 0.75);
  render3d::color c2(0.7, 0.1, 0.25);

  CHECK_EQ(c1 + c2, render3d::color(1.6, 0.7, 1.0));
}

TEST_CASE("subtracting colors") {
  render3d::color c1(0.9, 0.6, 0.75);
  render3d::color c2(0.7, 0.1, 0.25);

  CHECK_EQ(c1 - c2, render3d::color(0.2, 0.5, 0.5));
}

TEST_CASE("multiplying a color by a scalar") {
  render3d::color c(0.9, 0.6, 0.75);

  CHECK_EQ(c * 2.0, render3d::color(1.8, 1.2, 1.5));
}

TEST_CASE("multiplying a color by a scalar") {
  render3d::color c1(1.0, 0.2, 0.4);
  render3d::color c2(0.9, 1.0, 0.1);

  CHECK_EQ(c1 * c2, render3d::color(0.9, 0.2, 0.04));
}
