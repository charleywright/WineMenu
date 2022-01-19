#!/bin/bash

# ./run.sh lutris ../Menu/build/Release/WineMenu.dll GTA5.exe

if [ "$1" == "lutris" ]; then
  shift 
  # TODO Parse ~/.config/lutris/games/
  # TODO Use correct runner from ~/.local/share/lutris/runners/wine
  WINEPREFIX=$HOME/Games/epic-games-store WINEESYNC=1 $HOME/.local/share/lutris/runners/wine/lutris-fshack-6.21-6-x86_64/bin/wine ./build/Release/WineInjector.exe $@
fi
