#include "window.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

namespace core {
struct Window::Implementation {
  GLFWwindow* context;

  Implementation(const Specification& specification) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (specification.debug) {
      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    context = glfwCreateWindow(specification.width, specification.height,
                               specification.title.c_str(), nullptr, nullptr);

    if (!context) {
      std::cerr << "Failed to create GLFW window" << std::endl;
    }

    glfwMakeContextCurrent(context);

    glfwSwapInterval(specification.verticalSynchronization);

    glfwSetWindowUserPointer(context, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize OpenGL context" << std::endl;
    }
  }

  void clearBackground(const float red, const float green, const float blue,
                       const float alpha) {
    glClearColor(red, green, blue, alpha);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(context);
  }

  void destroy() {
    if (context) {
      glfwDestroyWindow(context);

      glfwTerminate();
    }

    context = nullptr;
  }

  bool shouldClose() const { return glfwWindowShouldClose(context); }

  void update() {
    if (glfwGetKey(context, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(context, GLFW_TRUE);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(context);

    glfwPollEvents();
  }

  uint32_t height() const {
    int height;

    glfwGetFramebufferSize(context, nullptr, &height);

    return static_cast<uint32_t>(height);
  }

  uint32_t width() const {
    int width;

    glfwGetFramebufferSize(context, &width, nullptr);

    return static_cast<uint32_t>(width);
  }

  float cursorX() const {
    double x;

    glfwGetCursorPos(context, &x, nullptr);

    return static_cast<float>(x);
  }

  float cursorY() const {
    double y;

    glfwGetCursorPos(context, nullptr, &y);

    return static_cast<float>(y);
  }
};

Window::Window(const Specification& specification)
    : pImpl(std::make_unique<Implementation>(specification)) {}

Window::~Window() { this->pImpl->destroy(); }

void Window::clearBackground(const float red, const float green,
                             const float blue, const float alpha) {
  this->pImpl->clearBackground(red, green, blue, alpha);
}

void Window::destroy() { this->pImpl->destroy(); }

bool Window::shouldClose() const { return this->pImpl->shouldClose(); }

void Window::update() { return this->pImpl->update(); }

uint32_t Window::height() const { return this->pImpl->height(); }

uint32_t Window::width() const { return this->pImpl->width(); }

float Window::cursorX() const { return this->pImpl->cursorX(); }

float Window::cursorY() const { return this->pImpl->cursorY(); }
};  // namespace core
