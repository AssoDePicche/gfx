#pragma once

#include <chrono>

namespace core {
  class Clock final {
    public:
      struct Tick final {
        double uptime;
        float delta;
      };

      Clock(const float);

      [[nodiscard]] Tick tick();

    private:
      std::chrono::time_point<std::chrono::high_resolution_clock> firstTick;
      std::chrono::time_point<std::chrono::high_resolution_clock> lastTick;
      float maxStep;
  };
}
