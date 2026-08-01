#include "main.h"

#include <core/application.h>
#include <core/window.h>

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>

int main(void) {
  std::string filepath = ".conf";

  if (!std::filesystem::exists(filepath)) {
    std::cerr << filepath << " not found" << std::endl;

    return 1;
  }

  core::Application::Specification specification =
      core::Application::Specification::from(filepath);

  core::Window::Specification windowSpecification;

  windowSpecification.title = specification.name;

  windowSpecification.width = specification.width;

  windowSpecification.height = specification.height;

  windowSpecification.debug = specification.debug;

  windowSpecification.verticalSynchronization =
      specification.verticalSynchronization;

  std::shared_ptr<core::Window> window =
      std::make_shared<core::Window>(windowSpecification);

  core::Application application(specification, window);

  application.push<MainLayer>(specification.width, specification.height);

  application.run();

  return 0;
}

MainLayer::MainLayer(const uint32_t width, const uint32_t height)
    : height(height), width(width) {}

void MainLayer::onAttach() {
  texture = std::make_shared<core::Texture>(width, height);

  buffer.resize(width * height * 3);
}

void MainLayer::onDetach() { texture.reset(); }

void MainLayer::onEvent(const core::Event& event) {}

void MainLayer::onRender(std::shared_ptr<core::Window> window,
                         const float delta) {
  texture->setData(buffer.data(), buffer.size());

  window->drawTexture(texture);
}

void MainLayer::onUpdate(const core::Clock::Tick& tick) {
  for (uint64_t j = 0u; j < height; ++j) {
    for (uint64_t i = 0u; i < width; ++i) {
      uint32_t index = (j * width + i) * 3;

      const uint16_t red = 255.999f * double(j) / (height - 1);

      const uint16_t green = 255.999f * double(i) / (width - 1);

      const uint16_t blue = 0;

      buffer[index + 0] = red;

      buffer[index + 1] = green;

      buffer[index + 2] = blue;
    }
  }
}
