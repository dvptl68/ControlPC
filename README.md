# Encryptor
A program that encrypts your files for you.

## How to use it:
Clone the project and compile it with GCC or MSVC or [download the exe](https://github.com/dvptl68/Encryptor/blob/master/bin/out.exe?raw=true), open a Windows terminal in the directory with the exe file , and run the program. With CMD, this can be done with: `filename.exe`, or in Git Bash: `./filename`.  
**Keep in mind that this program has been designed to work on Windows and is not cross-platform.**

## How it works:
In the src folder, there is a [main.cpp](https://github.com/dvptl68/Encryptor/blob/master/src/main.cpp) file and another folder called [class](https://github.com/dvptl68/Encryptor/tree/master/src/class), which contains all the class files. Most of the code in this program is in the class files, because each class represents a different stage of the program.  
  
You may notice that there is also a [scripts](https://github.com/dvptl68/Encryptor/tree/master/scripts) folder. The scripts in this folder are not part of the actual program, but they are scripts that helped expedite the development process. Each script is described below: 
- [rBash.sh](https://github.com/dvptl68/Encryptor/blob/master/scripts/rBash.sh) - Bash script that compiles and runs the program
- [rBatch.cmd](https://github.com/dvptl68/Encryptor/blob/master/scripts/rBatch.cmd) - CMD script that compiles and runs the program
- [updateBash.sh](https://github.com/dvptl68/Encryptor/blob/master/scripts/updateBash.sh) - Bash script that stages, commits, and pushes changes to the repository
- [updateBatch.cmd](https://github.com/dvptl68/Encryptor/blob/master/scripts/updateBatch.cmd) - CMD script that stages, commits, and pushes changes to the repository

## Contribute:
It is highly likely that this website has bugs that I missed, so if you find a bug, you can create an issue or fork this repository, fix the bug, and create a pull request!
