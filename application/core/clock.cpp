#include "clock.h"

#include <algorithm>

namespace core {
  Clock::Clock(const float maxStep) : firstTick(std::chrono::high_resolution_clock::now()), lastTick(firstTick), maxStep(maxStep) {}

  Clock::Tick Clock::tick() {
    const std::chrono::time_point<std::chrono::high_resolution_clock> currentTick = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<float> tickDuration = currentTick - lastTick;

    lastTick = currentTick;

    const std::chrono::duration<double> uptimeDuration = currentTick - firstTick;

    Tick tick;

    tick.delta = std::min(tickDuration.count(), maxStep);

    tick.uptime = uptimeDuration.count();

    return tick;
  }
}
