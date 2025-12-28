#pragma once

#include <GLFW/glfw3.h>

#include <core/window.h>

namespace platform {
  class GlfwWindow final : public core::Window {
    public:
      GlfwWindow(const core::Window::Specification &);

      void destroy() override;

      bool shouldClose() const override;

      void update() override;

      uint32_t height() const override;

      uint32_t width() const override;

      float cursorX() const override;

      float cursorY() const override;

    private:
      GLFWwindow *context;
  };
}
