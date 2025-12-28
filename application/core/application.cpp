#include "application.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <ranges>

#include "clock.h"
#include "event.h"
#include "window.h"

namespace core {
  Application::Application(const Application::Specification &specification, std::shared_ptr<Window> window) : specification(specification), clock(specification.maxFrameStep), window(window) {}

  Application::~Application() {
    window->destroy();
  }

  void Application::run() {
    running = true;

    const float deltaTime = 1.0f / static_cast<float>(specification.framesPerSecond);

    float accumulator = 0.0;

    while (running) {
      if (window->shouldClose()) {
        stop();     
      }

      const Clock::Tick tick = clock.tick();

      accumulator += tick.delta;

      while (accumulator >= deltaTime) {
        for (const auto& layer : stack) {
          layer->onUpdate(tick);
        }

        accumulator -= deltaTime;
      }

      const float alpha = accumulator / deltaTime;

      for (const auto& layer : stack) {
        layer->onRender(alpha);
      }

      window->update();
    }
  }

  void Application::stop() {
    running = false;
  }

  Application::Specification Application::Specification::from(const std::string &filepath) {
    Application::Specification specification;

    std::ifstream stream(filepath);

    if (!stream.is_open()) {
      return specification;
    }

    std::string line;

    std::string section;

    while (std::getline(stream, line)) {
      line = line.substr(0, line.find('#'));

      line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

      if (line.empty()) {
        continue;
      }

      if (line.front() == '[' && line.back() == ']') {
        section = line.substr(1, line.size() - 2);

        continue;
      }

      size_t delimiter = line.find('=');

      if (delimiter == std::string::npos) {
        continue;
      }

      std::string key = line.substr(0, delimiter);

      std::string value = line.substr(delimiter + 1);

      if (section == "Display") {
        if (key == "height") {
          specification.height = std::stoul(value);
        } else if (key == "width") {
          specification.width = std::stoul(value);
        }
      } else if (section == "Graphics") {
        if (key == "framesPerSecond") {
          specification.framesPerSecond = std::stoul(value);
        } else if (key == "fullscreen") {
          specification.fullscreen = value == "true";
        } else if (key == "maxFrameStep") {
          specification.maxFrameStep = std::stof(value);
        } else if (key == "verticalSynchronization") {
          specification.verticalSynchronization = value == "true";
        }
      } else if (section == "System") {
        if (key == "debug") {
          specification.debug = value == "true";
        }
      }
    }

    return specification;
  }
}
