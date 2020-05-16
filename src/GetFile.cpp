#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "GetFile.hpp"

using namespace std;

//Utility function to get a new tree
Tree newTree(string d){
  //Create a new tree, set the data, and return the tree
  Tree t;
  t.data = d;
  return t;
}

//Traverses all the files on the drive and places filenames in tree structure
void retrieveFiles(string& p, struct Tree& files, int& size){
  DIR *dir;
  struct dirent *e;
  //Convert the path into a char array
  const char *path = p.c_str();
  //Test if the given path is a directory
  if ((dir = opendir(path)) != NULL) {
    //Add a backslash to show that it is a directory
    files.data += "\\";
    //Populate the vector with filenames
    while ((e = readdir(dir)) != NULL) {
      string name = e->d_name;
      //Filter out unecessary files/directories
      if (name != "." && name != ".." && name != "System Volume Information" && (name.length() > 3 && name.substr(name.length()-4) != ".zip")){
        //Add file/directory to children vector and increase total size
        files.children.push_back(newTree(name));
        size++;
      }
    }
    closedir (dir);
    //Recursively call retrieveFiles on each child to fill subdirectories
    for (int i = 0; i < files.children.size(); i++){
      string path = p + files.children[i].data + "\\";
      retrieveFiles(path, files.children[i], size);
    }
  }
}

//Constructor for PickFile class
GetFile::GetFile(string p){
  //Set the path and name private variables
  GetFile::path = p.substr(0, 3);
  GetFile::name = p.substr(3);
  //Initialize the size to 0
  GetFile::size = 0;
  //Set the Tree private variable
  GetFile::files = newTree(GetFile::path + " -> \"" + GetFile::name + "\"");
  //Fill the vector with all available files
  retrieveFiles(GetFile::path, GetFile::files, GetFile::size);
}

//Returns a string with indentSize number of spaces
string getIndent(int indentSize){
  string indent = "";
  if (indentSize > 0){
    //Add spaces and then dashes for the indent size
    for (int i = 0; i < indentSize-3; i++){
      indent += " ";
    }
    for (int i = indentSize-3; i < indentSize; i++){
      indent += "-";
    }
    //Change one character to represent the tree structure
    indent[indentSize-3] = '|';
  }
  return indent;
}

//Traverses the filename tree and prints in orderly fashion
void traversePrint(struct Tree f, int indentSize){
  //Print data with number of indents preceding and make recursive call on each of the children
  cout << getIndent(indentSize) << f.data << "\n";
  for (int i = 0; i < f.children.size(); i++){
    traversePrint(f.children[i], indentSize + 3);
  }
}

//Uses helper functions to print all filenames to the user
void GetFile::printFiles(){
  if (GetFile::size > 0){
    //Print the number of files and call the recursive file print method
    cout << "\n" << GetFile::size << " available files: \n\n";
    traversePrint(GetFile::files, 0);
  }else{
    //Notify the user that there are no available files
    cout << "\nDrive " << GetFile::files.data.substr(0, GetFile::files.data.length()-1) << " has no available files!\n";
  }
}