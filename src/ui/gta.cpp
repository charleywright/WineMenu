#include "gta.hpp"
#include "natives.hpp"
#include "memory.hpp"

namespace Wine::UI
{
  void GTA::ShowNotification(std::string message)
  {
    HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message.c_str());
    HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
  }

  void GTA::ShowSubtitle(std::string message, int duration)
  {
    HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message.c_str());
    HUD::END_TEXT_COMMAND_PRINT(duration, true);
  }

  bool GTA::LoadTexture(std::filesystem::path path)
  {
    if (!std::filesystem::exists(path))
      return false;

    static std::uint32_t *(*FileRegister)(int *, const char *, bool, const char *, bool) = Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9", "RegisterTexture").Scan().As<decltype(FileRegister)>();
    int textureID;
    FileRegister(&textureID, path.generic_string().c_str(), true, path.filename().generic_string().c_str(), false);
    if (textureID == -1)
    {
      g_Logger->Error("Failed to register %s", path.c_str());
      return false;
    }
    else
    {
      g_Logger->Info("Loaded texture %s", path.filename().generic_string().c_str());
      return true;
    }
  }

  void GTA::DrawSprite(std::string dict, std::string texture, float x, float y, float width, float height, Color color, float rotation)
  {
    if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict.c_str()))
    {
      GRAPHICS::DRAW_SPRITE(dict.c_str(), texture.c_str(), x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0);
    }
    else
    {
      GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict.c_str(), false);
    }
  }

  void GTA::DrawRect(float x, float y, float width, float height, Color color)
  {
    GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
  }

  void GTA::DrawLeftText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
  {
    HUD::SET_TEXT_SCALE(size, size);
    HUD::SET_TEXT_FONT(static_cast<int>(font));
    HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
    if (outline)
      HUD::SET_TEXT_OUTLINE();
    if (shadow)
      HUD::SET_TEXT_DROP_SHADOW();

    HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
    HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
  }

  void GTA::DrawCenteredText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
  {
    HUD::SET_TEXT_CENTRE(true);
    DrawLeftText(text.c_str(), x, y, size, font, color, outline, shadow);
  }

  void GTA::DrawRightText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
  {
    HUD::SET_TEXT_WRAP(0.f, x);
    HUD::SET_TEXT_RIGHT_JUSTIFY(true);
    DrawLeftText(text.c_str(), x, y, size, font, color, outline, shadow);
  }

  float GTA::GetTextHeight(Font font, float size)
  {
    return HUD::GET_RENDERED_CHARACTER_HEIGHT(size, static_cast<int>(font));
  }

  Vector2 GTA::GetSpriteScale(float size)
  {
    int x;
    int y;
    GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

    return {(static_cast<float>(y) / static_cast<float>(x)) * size, size};
  }
}