#pragma once

#include <cstdint>
#include <string>

namespace core {
  class Window {
    public:
      struct Specification final {
        std::string title;
        uint32_t height;
        uint32_t width;
        bool debug;
        bool verticalSynchronization;
      };

      virtual ~Window() = default;

      virtual void destroy() = 0;

      virtual bool shouldClose() const = 0;

      virtual void update() = 0;

      virtual uint32_t height() const = 0;

      virtual uint32_t width() const = 0;

      virtual float cursorX() const = 0;

      virtual float cursorY() const = 0;
  };
}
