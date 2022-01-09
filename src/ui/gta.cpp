#include "gta.hpp"
#include "natives.hpp"

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
}