#include "texture.h"

#include <glad/glad.h>

namespace core {
struct Texture::Implementation {
  uint32_t _height;
  uint32_t _rendererID;
  uint32_t _width;

  Implementation(const uint32_t width, const uint32_t height)
      : _height(height), _width(width) {
    glGenTextures(1, &_rendererID);

    glBindTexture(GL_TEXTURE_2D, _rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, nullptr);
  }

  ~Implementation() { glDeleteTextures(1, &_rendererID); }

  void bind(const uint32_t offset) const {
    glActiveTexture(GL_TEXTURE0 + offset);

    glBindTexture(GL_TEXTURE_2D, _rendererID);
  }

  void setData(const void* buffer, const uint32_t size) {
    glBindTexture(GL_TEXTURE_2D, _rendererID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGB,
                    GL_UNSIGNED_BYTE, buffer);
  }

  uint32_t height() const { return _height; }

  uint32_t width() const { return _width; }
};

Texture::Texture(const uint32_t width, const uint32_t height)
    : pImpl(std::make_unique<Implementation>(width, height)) {}

Texture::~Texture() = default;

void Texture::bind(const uint32_t offset) const { pImpl->bind(offset); }

void Texture::setData(const void* buffer, const uint32_t size) {
  pImpl->setData(buffer, size);
}

uint32_t Texture::height() const { return pImpl->height(); }

uint32_t Texture::width() const { return pImpl->width(); }
}  // namespace core
