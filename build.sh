#!/bin/bash
if [ "$1" == "rebuild" ]; then
  rm -Rf build/*
  cd build
  WINEDEBUG=-all wine cmake ..
  cd ..
fi
WINEDEBUG=-all wine cmake --build build/ --config Release
