#pragma once
#include <string>
#include <filesystem>
#include "types.hpp"

namespace Wine::UI::GTA
{
  /**
   * @brief Shows a custom notification above the minimap
   * @param message The message to show. Supports TextModifier
   */
  void ShowNotification(std::string message);

  /**
   * @brief Shows custom subtitle
   * @param message The message to show. Supports TextModifier
   * @param duration How long to show the subtitle for in milliseconds
   */
  void ShowSubtitle(std::string message, int duration = 2000);

  /**
   * @brief Load a texture or sound into the game. Internally calls RegisterFile
   * @param path Path to the texture or sound
   * @return true if successful
   * @return false if unsuccesful
   */
  bool LoadTexture(std::filesystem::path path);

  /**
   * @brief Draw a sprite using natives
   * 
   * @param dict Dictionary of the sprite
   * @param texture Name of the sprite
   * @param x X co-ordinate between 0.f & 1.f
   * @param y Y co-ordinate between 0.f & 1.f
   * @param width Texture width between 0.f & 1.f
   * @param height Texture height between 0.f & 1.f
   * @param color Color of the texture. 255, 255, 255 for default
   * @param rotation Rotation of the texture
   */
  void DrawSprite(std::string dict, std::string texture, float x, float y, float width, float height, Color color, float rotation);

  /**
   * @brief Draw a rectangle using natives
   * 
   * @param x X co-ordinate between 0.f & 1.f
   * @param y Y co-ordinate between 0.f & 1.f
   * @param width Rectangle width between 0.f & 1.f
   * @param height Rectangle height between 0.f & 1.f
   * @param color Color of the rectangle. Use aircraft_dials.aircraft_dials_g0 sprite for gradients
   */
  void DrawRect(float x, float y, float width, float height, Color color);

  /**
   * @brief Draw text aligned to left using natives
   * 
   * @param text Text to draw
   * @param x X co-ordinate between 0.f & 1.f
   * @param y Y co-ordinate between 0.f & 1.f
   * @param size Font size
   * @param font Text font
   * @param color Color of the text
   * @param outline Draw the text with outline
   * @param shadow Draw the text with drop shadow
   */
  void DrawLeftText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);

  /**
   * @brief Draw centered text using natives
   * 
   * @param text Text to draw
   * @param x X co-ordinate between 0.f & 1.f
   * @param y Y co-ordinate between 0.f & 1.f
   * @param size Font size
   * @param font Text font
   * @param color Color of the text
   * @param outline Draw the text with outline
   * @param shadow Draw the text with drop shadow
   */
  void DrawCenteredText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);

  /**
   * @brief Draw text aligned to right using natives
   * 
   * @param text Text to draw
   * @param x X co-ordinate between 0.f & 1.f
   * @param y Y co-ordinate between 0.f & 1.f
   * @param size Font size
   * @param font Text font
   * @param color Color of the text
   * @param outline Draw the text with outline
   * @param shadow Draw the text with drop shadow
   */
  void DrawRightText(std::string text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);

  /**
   * @brief Get the height of a font
   * 
   * @param font Font to get the size of
   * @param size Size of the font
   * @return float 
   */
  float GetTextHeight(Font font, float size);

  /**
   * @brief Get width and height for a sprite
   * 
   * @param size The size the sprite should be
   * @return Vector2 
   */
  Vector2 GetSpriteScale(float size);
}