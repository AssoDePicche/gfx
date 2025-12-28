#include <string>

#include <core/application.h>
#include <platform/glfw.h>

int main(void) {
  std::string filepath = ".conf";

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

  return 0;
}
