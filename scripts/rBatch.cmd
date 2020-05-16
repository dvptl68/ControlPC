@echo off
echo.
echo Compiling...
cd ..
g++ -o bin/out src/encrypt.cpp src/DriveSelect.cpp src/GetFile.cpp
set /p answer="Done compiling! Run the program? (y/n): "
if "%answer%"=="y" (
  echo.
  cd bin
  out.exe
  cd ..
)