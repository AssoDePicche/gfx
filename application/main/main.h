#pragma once

#include <core/clock.h>
#include <core/event.h>
#include <core/layer.h>
#include <core/texture.h>
#include <core/window.h>

#include <cstdint>
#include <memory>
#include <vector>

class MainLayer final : public core::Layer {
 public:
  MainLayer(const uint32_t, const uint32_t);

  void onAttach() override;

  void onDetach() override;

  void onEvent(const core::Event&) override;

  void onRender(std::shared_ptr<core::Window>, const float) override;

  void onUpdate(const core::Clock::Tick&) override;

 private:
  uint32_t width;
  uint32_t height;
  std::shared_ptr<core::Texture> texture;
  std::vector<uint8_t> buffer;
};
