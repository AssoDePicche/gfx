#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include <core/application.h>
#include <platform/glfw.h>

int main(void) {
  std::string filepath = ".conf";

  if (!std::filesystem::exists(filepath)) {
    std::cerr << filepath << " not found" << std::endl;

    return 1;
  }

  core::Application::Specification specification = core::Application::Specification::from(filepath);

  core::Window::Specification windowSpecification;

  windowSpecification.title = specification.name;

  windowSpecification.width = specification.width;

  windowSpecification.height = specification.height;

  windowSpecification.debug = specification.debug;

  windowSpecification.verticalSynchronization = specification.verticalSynchronization;

  std::shared_ptr<core::Window> window = std::make_shared<platform::GlfwWindow>(windowSpecification);

  core::Application application(specification, window);

  application.run();


  const std::string filename = "settings.json";

  if (!std::filesystem::exists(filename)) {
    std::cerr << filename << " not found" << std::endl;

    return 1;
  }

  std::ifstream stream(filename);

  nlohmann::json json = nlohmann::json::parse(stream);

  const float aspect_ratio = json["aspect-ratio"];

  const uint64_t image_width = json["image-width"];

  uint64_t image_height = image_width / aspect_ratio;

  if (image_height < 1) {
    image_height = 1;
  }

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (uint64_t i = 0u; i < image_width; ++i) {
    for (uint64_t j = 0; j < image_height; ++j) {
      const uint16_t red = 255.999f * double(j) / (image_width - 1);

      const uint16_t green = 255.999f * double(i) / (image_height - 1);

      const uint16_t blue = 0;

      std::cout << red << " " << green << " " << blue << std::endl;
    }
  }
}
