#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "colors.hpp"

#include <string>
#include <vector>

namespace render3d {
  class canvas {
  public:
    constexpr explicit canvas(int width, int height)
        : m_width(width), m_height(height),
          m_board(width * height, color(0.0, 0.0, 0.0)) {}

    constexpr explicit canvas(int width, int height, const color<double>& color)
        : m_width(width), m_height(height), m_board(width * height, color) {}

    [[nodiscard]] constexpr int width() const noexcept { return m_width; }
    [[nodiscard]] constexpr int height() const noexcept { return m_height; }

    [[nodiscard]] color<double> pixel_at(int col, int row) const;

    void write_pixel(int col, int row, const color<double>& c);

    void write_ppm(const std::string& file_name) const;

    [[nodiscard]] constexpr color<double> operator()(int col, int row) const {
      return m_board.at(row * m_width + col);
    }

    [[nodiscard]] constexpr color<double>& operator()(int col, int row) {
      return m_board.at(row * m_width + col);
    }

  private:
    int m_width, m_height;
    std::vector<color<double>> m_board;
  };
} // namespace render3d

#endif // !CANVAS_HPP
