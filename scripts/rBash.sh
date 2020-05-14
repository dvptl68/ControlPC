#!/bin/bash

echo
echo "Compiling..."
if [ "${PWD##*/}" = "scripts" ]; then
  cd ..
fi
g++ -o bin/out src/encrypt.cpp src/Select.cpp
read -p "Done compiling! Run the program? (y/n): " answer
if [ "${answer,,}" = "y" ]; then
  echo
  ./bin/out.exe
fi
