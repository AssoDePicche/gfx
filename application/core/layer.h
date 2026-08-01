#pragma once

#include <memory.h>

#include "clock.h"
#include "event.h"
#include "window.h"

namespace core {
class Layer {
 public:
  virtual ~Layer() = default;

  virtual void onAttach() = 0;

  virtual void onDetach() = 0;

  virtual void onEvent(const Event&) = 0;

  virtual void onRender(std::shared_ptr<Window>, const float) = 0;

  virtual void onUpdate(const Clock::Tick&) = 0;
};
}  // namespace core
