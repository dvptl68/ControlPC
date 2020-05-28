@echo off
echo.
echo Compiling...
cd ..
g++ -o bin/encryptor src/main.cpp src/class/DriveSelect.cpp src/class/GetFile.cpp src/class/FileData.cpp src/class/EFile.cpp
set /p answer="Done compiling! Run the program? (y/n): "
if "%answer%"=="y" (
  echo.
  cd bin
  encryptor.exe
  cd ..
)