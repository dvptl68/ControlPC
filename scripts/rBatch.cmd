@echo off
echo.
echo Compiling...
g++ -o bin/control.exe src/control.cpp
set /p answer="Done compiling! Run the program? (y/n): "
if "%answer%"=="y" (
  echo.
  cd bin
  control.exe
  cd ..
)