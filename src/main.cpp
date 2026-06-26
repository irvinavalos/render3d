#include <print>

#include <canvas.hpp>
#include <math/geometry.hpp>

struct projectile {
  math::point3<double> position;
  math::vec3<double> velocity;
};

struct environment {
  math::vec3<double> gravity;
  math::vec3<double> wind;
};

constexpr void tick(const environment& env, projectile& proj) noexcept {
  proj.position = proj.position + proj.velocity;
  proj.velocity = proj.velocity + env.gravity + env.wind;
}

constexpr void projectile_motion() {
  auto start = math::point3(0.0, 1.0, 0.0);
  auto velocity = math::normalize(math::vec3(1.0, 1.8, 0.0)) * 11.25;

  auto p = projectile(start, velocity);

  auto gravity = math::vec3(0.0, -0.1, 0.0);
  auto wind = math::vec3(-0.01, 0.0, 0.0);

  auto e = environment(gravity, wind);

  render3d::canvas canvas(1280, 720, render3d::color(1.0, 1.0, 1.0));
  render3d::color projectile_color = render3d::color(0.0, 0.0, 1.0);

  std::string file_name{"images/projectile_motion.ppm"};

  std::println("t_0: (x={}, y={})", p.position.x(), p.position.y());

  for (int n{1}; n <= 200; ++n) {
    if (p.position.y() < 0)
      break;

    auto x = static_cast<int>(p.position.x());
    auto y = canvas.height() - static_cast<int>(p.position.y());

    std::println("t_{}: (x={}, y={})", n, x, y);

    // O---------> x
    // |
    // |
    // |
    // y

    canvas.write_pixel(x, y, projectile_color);
    tick(e, p);
  }

  canvas.write_ppm(file_name);
}

void draw_5x5square(render3d::canvas& canvas, math::point3<double> p,
                    const render3d::color<double>& color) {
  int x = static_cast<int>(p.x());
  int y = static_cast<int>(p.y());

  canvas.write_pixel(x, y, color);
  canvas.write_pixel(x, y - 1, color);
  canvas.write_pixel(x, y - 2, color);
  canvas.write_pixel(x, y + 1, color);
  canvas.write_pixel(x, y + 2, color);
  // left
  canvas.write_pixel(x - 1, y, color);
  canvas.write_pixel(x - 2, y, color);
  // left + up
  canvas.write_pixel(x - 1, y + 1, color);
  canvas.write_pixel(x - 2, y + 1, color);
  canvas.write_pixel(x - 1, y + 2, color);
  canvas.write_pixel(x - 2, y + 2, color);
  // left + down
  canvas.write_pixel(x - 1, y - 1, color);
  canvas.write_pixel(x - 2, y - 1, color);
  canvas.write_pixel(x - 1, y - 2, color);
  canvas.write_pixel(x - 2, y - 2, color);
  // right
  canvas.write_pixel(x + 1, y, color);
  canvas.write_pixel(x + 2, y, color);
  // right + up
  canvas.write_pixel(x + 1, y + 1, color);
  canvas.write_pixel(x + 2, y + 1, color);
  canvas.write_pixel(x + 1, y + 2, color);
  canvas.write_pixel(x + 2, y + 2, color);
  // right + down
  canvas.write_pixel(x + 1, y - 1, color);
  canvas.write_pixel(x + 2, y - 1, color);
  canvas.write_pixel(x + 1, y - 2, color);
  canvas.write_pixel(x + 2, y - 2, color);
}

int main() {
  auto white = render3d::color(1.0, 1.0, 1.0);
  auto black = render3d::color(0.0, 0.0, 0.0);

  const auto width = 500;
  const auto height = 500;

  const auto half_width_f64 = width / 2.0;
  const auto half_height_f64 = height / 2.0;

  const auto half_width_int = static_cast<int>(half_width_f64);
  const auto half_height_int = static_cast<int>(half_height_f64);

  auto canvas = render3d::canvas(width, height, white);
  const std::string file_name{"images/clock.ppm"};

  const auto p = math::point3(half_width_f64, half_height_f64, 0.0);

  for (int k{0}; k <= 11; ++k) {
    const auto T = math::translation(
        std::cos(math::PI / 6.0 * k) * half_width_f64 * 0.5,
        std::sin(math::PI / 6.0 * k) * half_height_f64 * 0.5, 0.0);
    draw_5x5square(canvas, T * p, black);
  }

  canvas.write_ppm(file_name);

  return 0;
}
