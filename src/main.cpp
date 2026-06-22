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

int main() {
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

  return 0;
}
