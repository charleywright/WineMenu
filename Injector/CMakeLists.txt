cmake_minimum_required(VERSION 3.10)
project(WineInjector VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_executable(WineInjector
  src/main.cpp
)
target_link_libraries(WineInjector)
