# Encryptor
A program that encrypts your files for you.

## How to use it:
Clone the project and compile it with GCC or MSVC or [download the executable](https://github.com/dvptl68/Encryptor/blob/master/bin/encryptor.exe?raw=true), open a Windows terminal in the directory with the .exe file , and run the program. With CMD, this can be done by simply typing: `encryptor.exe`, or in a Bash terminal such as Git Bash (not recommended): `./encryptor`.  
  
**Keep in mind that this program has been designed to work on Windows and is not cross-platform.**

## How it works:
In the src folder, there is a [main.cpp](https://github.com/dvptl68/Encryptor/blob/master/src/main.cpp) file and another folder called [class](https://github.com/dvptl68/Encryptor/tree/master/src/class), which contains all the class files. Most of the code in this program belongs to the class files, because each class represents a different stage of the program.  
  
Traversing the filesystem and storing directory information was the most challenge part of this project. I created a data structure I called "tree", with two members: data and a vector of "tree" called children. The recursive design of this data structure models a filesystem perfectly, and is useful for storing directory information, printing files in a tree view, and searching for specific files.  
  
You may notice that there is also a [scripts](https://github.com/dvptl68/Encryptor/tree/master/scripts) folder. The scripts in this folder are not part of the actual program, but they are scripts that helped expedite the development process. Each script is described below: 
- [run.sh](https://github.com/dvptl68/Encryptor/blob/master/scripts/run.sh) - Bash script that compiles and runs the program
- [run.cmd](https://github.com/dvptl68/Encryptor/blob/master/scripts/run.cmd) - CMD script that compiles and runs the program
- [update.sh](https://github.com/dvptl68/Encryptor/blob/master/scripts/update.sh) - Bash script that stages, commits, and pushes changes to the repository
- [update.cmd](https://github.com/dvptl68/Encryptor/blob/master/scripts/update.cmd) - CMD script that stages, commits, and pushes changes to the repository

## Contribute:
There may be bugs that I missed, so if you find a bug, you can create an issue or fork this repository, fix the bug, and create a pull request!
