#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "texture.h"

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

  void drawTexture(const std::shared_ptr<Texture>&);

  [[nodiscard]] bool shouldClose() const;

  void update();

  [[nodiscard]] uint32_t height() const;

  [[nodiscard]] uint32_t width() const;

  [[nodiscard]] float cursorX() const;

  [[nodiscard]] float cursorY() const;

 private:
  struct Implementation;
  std::unique_ptr<Implementation> pImpl;
};
}  // namespace core
