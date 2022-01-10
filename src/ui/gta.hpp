#pragma once
#include <string>
#include <filesystem>
#include "types.hpp"

namespace Wine::UI::GTA
{
  void ShowNotification(std::string message);
  void ShowSubtitle(std::string message, int duration = 2000);
  bool LoadTexture(std::filesystem::path path);
  void DrawSprite(std::string dict, std::string texture, float x, float y, float width, float height, Color color, float rotation);
}