cmake_minimum_required(VERSION 3.10)
project(WineMenu VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(src include)
add_library(WineMenu SHARED
  src/main.cpp
  src/logger.cpp
  src/game.cpp
  src/hooking.cpp
  src/config.cpp
  src/translations.cpp
  
  src/ui/d3dRenderer.cpp
  src/ui/uiRenderer.cpp
  src/ui/gta.cpp
  
  include/ImGui/imgui_demo.cpp
  include/ImGui/imgui_draw.cpp
  include/ImGui/imgui_impl_dx11.cpp
  include/ImGui/imgui_impl_win32.cpp
  include/ImGui/imgui_widgets.cpp
  include/ImGui/imgui.cpp
)
target_link_libraries(WineMenu ../lib/minhook d3dcompiler shlwapi)
