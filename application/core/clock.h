#pragma once

#include <memory>

namespace core {
class Clock final {
 public:
  struct Tick final {
    double uptime;
    float delta;
  };

  Clock(const float);

  ~Clock();

  [[nodiscard]] Tick tick();

 private:
  struct Implementation;
  std::unique_ptr<Implementation> pImpl;
};
}  // namespace core
