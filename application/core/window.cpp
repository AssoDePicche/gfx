#include "window.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

namespace core {
struct Data {
  GLuint vertexArrayObjectsId = 0;
  GLuint vertexBufferObjectsId = 0;
  GLuint shaderProgram = 0;
};

static Data s_Data;

static const char* vertexShaderSource = R"(
      #version 330 core
      layout (location = 0) in vec2 aPos;
      layout (location = 1) in vec2 aTexCoord;
      out vec2 TexCoord;
      void main() {
          gl_Position = vec4(aPos, 0.0, 1.0);
          TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
      }
  )";

static const char* fragmentShaderSource = R"(
      #version 330 core
      out vec4 FragColor;
      in vec2 TexCoord;
      uniform sampler2D screenTexture;
      void main() {
          FragColor = texture(screenTexture, TexCoord);
      }
  )";

static void checkShader(GLuint shader, const std::string& type) {
  GLint success;

  GLchar infoLog[1024];

  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

      std::cerr << "[GL Shader Error] " << type << "\n" << infoLog << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);

      std::cerr << "[GL Program Error] " << type << "\n"
                << infoLog << std::endl;
    }
  }
}

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

      glfwTerminate();

      exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(context);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "[GLAD Error] Failed to load OpenGL function pointers!"
                << std::endl;

      exit(EXIT_FAILURE);
    }

    glfwSwapInterval(specification.verticalSynchronization);

    glfwSetWindowUserPointer(context, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize OpenGL context" << std::endl;
    }

    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);

    glCompileShader(vertexShaderId);

    checkShader(vertexShaderId, "VERTEX");

    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);

    glCompileShader(fragmentShaderId);

    checkShader(fragmentShaderId, "FRAGMENT");

    s_Data.shaderProgram = glCreateProgram();

    glAttachShader(s_Data.shaderProgram, vertexShaderId);

    glAttachShader(s_Data.shaderProgram, fragmentShaderId);

    glLinkProgram(s_Data.shaderProgram);

    checkShader(s_Data.shaderProgram, "PROGRAM");

    glDeleteShader(vertexShaderId);

    glDeleteShader(fragmentShaderId);

    glUseProgram(s_Data.shaderProgram);

    glUniform1i(glGetUniformLocation(s_Data.shaderProgram, "screenTexture"), 0);

    float vertices[] = {-1.0f, 1.0f,  0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                        1.0f,  -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
                        1.0f,  -1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  1.0f, 0.0f};

    glGenVertexArrays(1, &s_Data.vertexArrayObjectsId);

    glGenBuffers(1, &s_Data.vertexBufferObjectsId);

    glBindVertexArray(s_Data.vertexArrayObjectsId);

    glBindBuffer(GL_ARRAY_BUFFER, s_Data.vertexBufferObjectsId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)0);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)(2 * sizeof(float)));

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
  }

  void drawTexture(const std::shared_ptr<Texture>& texture) {
    if (!texture || s_Data.shaderProgram == 0) return;

    glViewport(0, 0, texture->width(), texture->height());

    glDisable(GL_DEPTH_TEST);

    texture->bind(0);

    glUseProgram(s_Data.shaderProgram);

    glBindVertexArray(s_Data.vertexArrayObjectsId);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
  }

  void clearBackground(const float red, const float green, const float blue,
                       const float alpha) {
    glClearColor(red, green, blue, alpha);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(context);
  }

  void destroy() {
    if (s_Data.shaderProgram != 0) {
      glDeleteVertexArrays(1, &s_Data.vertexArrayObjectsId);

      glDeleteBuffers(1, &s_Data.vertexBufferObjectsId);

      glDeleteProgram(s_Data.shaderProgram);

      s_Data.shaderProgram = 0;
    }

    if (context) {
      glfwDestroyWindow(context);

      glfwTerminate();

      context = nullptr;
    }
  }

  bool shouldClose() const { return glfwWindowShouldClose(context); }

  void update() {
    if (glfwGetKey(context, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(context, GLFW_TRUE);
    }

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

void Window::drawTexture(const std::shared_ptr<Texture>& texture) {
  pImpl->drawTexture(texture);
}

bool Window::shouldClose() const { return this->pImpl->shouldClose(); }

void Window::update() { return this->pImpl->update(); }

uint32_t Window::height() const { return this->pImpl->height(); }

uint32_t Window::width() const { return this->pImpl->width(); }

float Window::cursorX() const { return this->pImpl->cursorX(); }

float Window::cursorY() const { return this->pImpl->cursorY(); }
};  // namespace core
