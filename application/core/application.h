#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "layer.h"

namespace core {
  class Clock;
  class Window;

  class Application final {
    public:
      struct Specification final {
        std::string name = "Gfx";
        uint32_t framesPerSecond = 60;
        uint32_t height = 720;
        uint32_t width = 1280;
        float maxFrameStep = 0.25f;
        bool debug = false;
        bool fullscreen = false;
        bool verticalSynchronization = true;

        static Specification from(const std::string &);
      };

      Application(const Specification &, std::shared_ptr<Window>);

      ~Application();

      Application(const Application &) = delete;

      Application &operator=(const Application &) = delete;

      void run();

      void stop();

      template<typename T, typename... Args>
      requires std::derived_from<T, Layer>
      void push(Args&&... args) {
        stack.push_back(std::make_unique<T>(std::forward<Args>(args)...));
      }

    private:
      Specification specification;
      Clock clock;
      std::vector<std::unique_ptr<Layer>> stack;
      std::shared_ptr<Window> window;
      bool running = false;
  };
}
