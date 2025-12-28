#pragma once

#include "clock.h"
#include "event.h"

namespace core {
  class Layer {
    public:
        virtual ~Layer() = default;

        virtual void onEvent(const Event &) = 0;

        virtual void onRender(const float) = 0;

        virtual void onUpdate(const Clock::Tick &) = 0;
  };
}
