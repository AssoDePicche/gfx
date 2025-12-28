#include "glfw.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <iostream>

namespace platform {
  GlfwWindow::GlfwWindow(const core::Window::Specification &specification) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (specification.debug) {
      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    context = glfwCreateWindow(specification.width, specification.height, specification.title.c_str(), nullptr, nullptr);

    if (!context) {
      std::cerr << "Failed to create GLFW window" <<std::endl;
    }

    glfwMakeContextCurrent(context);

    int swapInterval = specification.verticalSynchronization ? 1 : 0; 

    glfwSwapInterval(swapInterval);

    glfwSetWindowUserPointer(context, this);
  }

  void GlfwWindow::destroy() {
    if (context) {
      glfwDestroyWindow(context);

      glfwTerminate();
    }

    context = nullptr;
  }

  bool GlfwWindow::shouldClose() const {
    return glfwWindowShouldClose(context);
  }

  void GlfwWindow::update() {
    if (glfwGetKey(context, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(context, GLFW_TRUE); 
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(context);

    glfwPollEvents();
  }

  uint32_t GlfwWindow::height() const {
    int height;

    glfwGetFramebufferSize(context, nullptr, &height);

    return static_cast<uint32_t>(height);
  }

  uint32_t GlfwWindow::width() const {
    int width;

    glfwGetFramebufferSize(context, &width, nullptr);

    return static_cast<uint32_t>(width);
  }

  float GlfwWindow::cursorX() const {
    double x;

    glfwGetCursorPos(context, &x, nullptr);

    return static_cast<float>(x);
  }

  float GlfwWindow::cursorY() const {
    double y;

    glfwGetCursorPos(context, nullptr, &y);

    return static_cast<float>(y);
  }
}
