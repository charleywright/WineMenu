cmake_minimum_required(VERSION 3.10)
project(WineMenu VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_library(WineMenu SHARED
  src/main.cpp
  src/logger.cpp
  src/game.cpp
)
