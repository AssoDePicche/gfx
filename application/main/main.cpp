#include "main.h"

#include <core/application.h>
#include <core/window.h>

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

  application.push<MainLayer>();

  application.run();
}
