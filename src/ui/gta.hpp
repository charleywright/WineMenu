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
  void DrawRect(float x, float y, float width, float height, Color color);
  void DrawLeftText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
  void DrawCenteredText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
  void DrawRightText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
  float GetTextHeight(Font font, float size);
  Vector2 GetSpriteScale(float size);
}