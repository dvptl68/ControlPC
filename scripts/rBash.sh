#!/bin/bash

echo
echo "Compiling..."
if [ "${PWD##*/}" = "scripts" ]; then
  cd ..
fi
g++ -o bin/out src/main.cpp src/DriveSelect.cpp src/GetFile.cpp
read -p "Done compiling! Run the program? (y/n): " answer
if [ "${answer,,}" = "y" ]; then
  echo
  ./bin/out.exe
fi
