#!/bin/bash

echo
echo "Compiling..."
g++ -o bin/control src/control.cpp
read -p "Done compiling! Run the program? (y/n): " answer
if [ "${answer,,}" = "y" ]; then
  echo
  ./bin/control.exe
fi
