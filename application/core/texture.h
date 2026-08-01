#pragma once

#include <cstdint>
#include <memory>

namespace core {
class Texture {
 public:
  Texture(const uint32_t, const uint32_t);

  ~Texture();

  void bind(const uint32_t = 0) const;

  void setData(const void*, const uint32_t);

  [[nodiscard]] uint32_t height() const;

  [[nodiscard]] uint32_t width() const;

 private:
  struct Implementation;
  std::unique_ptr<Implementation> pImpl;
};
}  // namespace core
