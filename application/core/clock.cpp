#include "clock.h"

#include <chrono>

namespace core {
struct Clock::Implementation {
  std::chrono::time_point<std::chrono::high_resolution_clock> firstTick;
  std::chrono::time_point<std::chrono::high_resolution_clock> lastTick;
  float maxStep;

  Implementation(const float maxStep)
      : firstTick(std::chrono::high_resolution_clock::now()),
        lastTick(firstTick),
        maxStep(maxStep) {}

  Clock::Tick tick() {
    const std::chrono::time_point<std::chrono::high_resolution_clock>
        currentTick = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<float> tickDuration = currentTick - lastTick;

    lastTick = currentTick;

    const std::chrono::duration<double> uptimeDuration =
        currentTick - firstTick;

    Tick tick;

    tick.delta = std::min(tickDuration.count(), maxStep);

    tick.uptime = uptimeDuration.count();

    return tick;
  }
};

Clock::Clock(const float maxStep)
    : pImpl(std::make_unique<Implementation>(maxStep)) {}

Clock::~Clock() {}

Clock::Tick Clock::tick() { return pImpl->tick(); }
}  // namespace core
