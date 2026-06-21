#include <print>

#include <math/geometry.hpp>

struct projectile {
  math::point3<double> position;
  math::vec3<double> velocity;
};

struct environment {
  math::vec3<double> gravity;
  math::vec3<double> wind;
};

[[nodiscard]] constexpr projectile tick(environment env,
                                        projectile proj) noexcept {
  auto position = proj.position + proj.velocity;
  auto velocity = proj.velocity + env.gravity + env.wind;
  return projectile(position, velocity);
}

int main() {
  auto p = projectile(math::point3(0.0, 1.0, 0.0),
                      math::normalize(math::vec3(1.0, 1.0, 0.0)));

  auto e = environment(math::vec3(0.0, -0.1, 0.0), math::vec3(-0.01, 0.0, 0.0));

  std::println("{}", p.position.y());
  for (int i{}; i < 17; ++i) {
    p = tick(e, p);
  }
  std::println("{}", p.position.y());
  return 0;
}
