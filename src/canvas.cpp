#include "canvas.hpp"

#include <format>
#include <fstream>
#include <stdexcept>

static constexpr int MIN_RGB_VAL{0};
static constexpr int MAX_RGB_VAL{255};

static int rgb_float_to_int(double val) noexcept {
  return std::clamp(static_cast<int>(val), MIN_RGB_VAL, MAX_RGB_VAL);
}

static int num_digits(int val) noexcept {
  if (val < 10)
    return 1;
  if (val < 100)
    return 2;
  return 3;
}

static constexpr void write_value(std::ofstream& file, int val, int& col) {
  auto len = num_digits(val);
  if (col == 0) {
    file << val;
    col = len;
  } else if (col + 1 + len > 70) {
    file << "\n" << val;
    col = len;
  } else {
    file << " " << val;
    col += 1 + len;
  }
}

render3d::color<double> render3d::canvas::pixel_at(int col, int row) const {
  auto idx = row * m_width + col;

  if (idx >= m_board.size()) {
    throw std::out_of_range(std::format(
        "ERROR: pixel at (x={}, y={}) is out of bounds\n", col, row));
  }

  return (*this)(col, row);
}

void render3d::canvas::write_pixel(int col, int row, const color<double>& c) {
  auto idx = row * m_width + col;

  if (idx >= m_board.size()) {
    throw std::out_of_range(std::format(
        "ERROR: pixel at (x={}, y={}) is out of bounds\n", col, row));
  }

  (*this)(col, row) = c;
}

void render3d::canvas::write_ppm(const std::string& file_name) const {
  std::ofstream file(file_name);

  if (!file.is_open()) {
    throw std::runtime_error(
        std::format("ERROR: could not open file = {}\n", file_name));
  }

  // constructing PPM header
  file << "P3\n";
  file << width() << " " << height() << "\n";
  file << "255\n";

  for (int r{}; r < height(); r++) {
    auto column_count = 0;
    for (int c{}; c < width(); ++c) {
      auto pixel = 255.0 * pixel_at(c, r);

      write_value(file, rgb_float_to_int(pixel.red()), column_count);
      write_value(file, rgb_float_to_int(pixel.green()), column_count);
      write_value(file, rgb_float_to_int(pixel.blue()), column_count);
    }
    file << "\n";
  }
  file << "\n";

  file.close();
}
