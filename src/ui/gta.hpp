#pragma once
#include <string>

namespace Wine::UI::GTA
{
  void ShowNotification(std::string message);
  void ShowSubtitle(std::string message, int duration = 2000);
}