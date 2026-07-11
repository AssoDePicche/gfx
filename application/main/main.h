#pragma once

#include <core/clock.h>
#include <core/event.h>
#include <core/layer.h>

#include <algorithm>
#include <cstdint>
#include <iostream>

class MainLayer : public core::Layer {
  void onEvent(const core::Event& event) override {}

  void onRender(const float delta) override {
    const float aspect_ratio = 16.0f / 9.0f;

    const uint64_t image_width = 1080;

    const uint64_t image_height =
        static_cast<uint64_t>(std::max(image_width / aspect_ratio, 1.0f));

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (uint64_t i = 0u; i < image_width; ++i) {
      for (uint64_t j = 0u; j < image_height; ++j) {
        const uint16_t red = 255.999f * double(j) / (image_width - 1);

        const uint16_t green = 255.999f * double(i) / (image_height - 1);

        const uint16_t blue = 0;

        std::cout << red << " " << green << " " << blue << std::endl;
      }
    }
  }

  void onUpdate(const core::Clock::Tick& tick) override {}
};
