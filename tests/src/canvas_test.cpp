#include <canvas.hpp>
#include <doctest.h>

#include <fstream>
#include <string>

const std::string image_tests{"../images/tests/"};

TEST_CASE("creating a canvas") {
  render3d::canvas canvas(10, 20);

  CHECK_EQ(canvas.width(), 10);
  CHECK_EQ(canvas.height(), 20);

  // make sure each pixel is initially black
  render3d::color black(0.0, 0.0, 0.0);
  for (int i{}; i < canvas.height(); ++i) {
    for (int j{}; j < canvas.width(); ++j) {
      CHECK_EQ(canvas.pixel_at(j, i), black);
    }
  }
}

TEST_CASE("writing pixels to a canvas") {
  render3d::canvas canvas(10, 20);
  render3d::color red(1.0, 0.0, 0.0);

  canvas.write_pixel(2, 3, red);

  CHECK_EQ(canvas.pixel_at(2, 3), red);
}

TEST_CASE("constructing PPM header") {
  render3d::canvas canvas(10, 20);

  std::string file_name = image_tests + "test_ppm_header.ppm";
  canvas.write_ppm(file_name);

  std::ifstream file(file_name);
  REQUIRE(file.is_open());

  std::string line;

  std::getline(file, line);
  CHECK_EQ(line, "P3");

  std::getline(file, line);
  CHECK_EQ(line, "10 20");

  std::getline(file, line);
  CHECK_EQ(line, "255");

  file.close();
}

TEST_CASE("constructing the PPM pixel data") {
  render3d::canvas canvas(5, 3);

  render3d::color c1(1.5, 0.0, 0.0);
  render3d::color c2(0.0, 0.5, 0.0);
  render3d::color c3(-0.5, 0.0, 1.0);

  canvas.write_pixel(0, 0, c1);
  canvas.write_pixel(2, 1, c2);
  canvas.write_pixel(4, 2, c3);

  std::string file_name = image_tests + "test_ppm_data.ppm";
  canvas.write_ppm(file_name);

  std::ifstream file(file_name);
  REQUIRE(file.is_open());

  std::string line;

  std::getline(file, line);
  std::getline(file, line);
  std::getline(file, line);

  std::getline(file, line);
  CHECK_EQ(line, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

  std::getline(file, line);
  CHECK_EQ(line, "0 0 0 0 0 0 0 127 0 0 0 0 0 0 0");

  std::getline(file, line);
  CHECK_EQ(line, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");

  file.close();
}

TEST_CASE("splitting long lines in PPM files") {
  render3d::color c(1.0, 0.8, 0.6);
  render3d::canvas canvas(10, 2, c);

  std::string file_name = image_tests + "test_ppm_long_lines.ppm";
  canvas.write_ppm(file_name);

  std::ifstream file(file_name);
  REQUIRE(file.is_open());

  std::string line;

  std::getline(file, line);
  std::getline(file, line);
  std::getline(file, line);

  std::getline(file, line);
  CHECK_EQ(
      line,
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");

  std::getline(file, line);
  CHECK_EQ(line, "153 255 204 153 255 204 153 255 204 153 255 204 153");

  std::getline(file, line);
  CHECK_EQ(
      line,
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");

  std::getline(file, line);
  CHECK_EQ(line, "153 255 204 153 255 204 153 255 204 153 255 204 153");

  file.close();
}

TEST_CASE("PPM files end with a newline character") {
  render3d::canvas canvas(5, 3);

  std::string file_name = image_tests + "test_ppm_end_newline.ppm";
  canvas.write_ppm(file_name);

  std::ifstream file(file_name);

  REQUIRE(file.is_open());
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());

  CHECK(content.back() == '\n');

  file.close();
}
