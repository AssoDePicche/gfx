#pragma once

#include <cstdint>
#include <memory>
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

  Window(const Specification&);

  ~Window();

  void clearBackground(const float, const float, const float, const float);

  void destroy();

  bool shouldClose() const;

  void update();

  uint32_t height() const;

  uint32_t width() const;

  float cursorX() const;

  float cursorY() const;

 private:
  struct Implementation;
  std::unique_ptr<Implementation> pImpl;
};
}  // namespace core
