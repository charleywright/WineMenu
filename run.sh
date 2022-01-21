#!/bin/bash

# Usage: run.sh <target> [rebuild]

INJECTOR_DELAY=3
INJECTOR_CMD="./Injector/build/Release/WineInjector.exe ./Menu/build/Release/WineMenu.dll GTA5.exe $INJECTOR_DELAY"
blue=$(tput setaf 4)
normal=$(tput sgr0)

set -e
if [ "$2" == "rebuild" ]; then
  cd Menu
  rm -Rf build/*
  cd build
  printf "\x1B[32mBuilding Menu...\n\x1B[0m"
  WINEDEBUG=-all wine cmake ..
  WINEDEBUG=-all wine cmake --build . --config Release
  cd ../../
  cd Injector
  rm -Rf build/*
  cd build
  printf "\x1B[32m\n\nBuilding Injector...\n\x1B[0m"
  WINEDEBUG=-all wine cmake ..
  WINEDEBUG=-all wine cmake --build . --config Release
  cd ../../
else
  cd Menu
  printf "\x1B[32mBuilding Menu...\n\x1B[0m"
  WINEDEBUG=-all wine cmake --build build/ --config Release
  cd ../Injector
  printf "\x1B[32m\n\nBuilding Injector...\n\x1B[0m"
  WINEDEBUG=-all wine cmake --build build/ --config Release
  cd ..
fi

if [ "$1" == "lutris" ]; then
  printf "\x1B[32m\n\nInjecting...\n\x1B[0m"
  WINEPREFIX=$HOME/Games/epic-games-store WINEDEBUG=-all WINEESYNC=1 $HOME/.local/share/lutris/runners/wine/lutris-fshack-6.21-6-x86_64/bin/wine $INJECTOR_CMD
fi

# TODO Steam support