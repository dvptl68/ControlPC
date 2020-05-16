#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "PickFile.hpp"

using namespace std;

//Utility function to get a new tree
Tree newTree(string d){
  //Create a new tree, set the data, and return the tree
  Tree t;
  t.data = d;
  return t;
}

//Traverses all the files on the drive and places filenames in tree structure
void retrieveFiles(string& p, struct Tree& files){
  DIR *dir;
  struct dirent *e;
  //Convert the path into a char array
  const char *path = p.c_str();
  //Test if the given path is a directory
  if ((dir = opendir(path)) != NULL) {
    //Populate the vector with filenames
    while ((e = readdir(dir)) != NULL) {
      string name = e->d_name;
      if (name != "." && name != ".."){
        files.children.push_back(newTree(name));
      }
    }
    closedir (dir);
    for (int i = 0; i < files.children.size(); i++){
      string path = p + files.children[i].data + "\\";
      retrieveFiles(path, files.children[files.children.size()-1]);
    }
  }
}

//Constructor for PickFile class
PickFile::PickFile(string p){
  //Set the path and name private variables
  PickFile::path = p.substr(0, 3);
  PickFile::name = p.substr(3);
  //Set the Tree private variable
  PickFile::files = newTree(PickFile::path + " -> \"" + PickFile::name + "\"");
  //Fill the vector with all available files
  retrieveFiles(PickFile::path, PickFile::files);
}

//Returns a string with indentSize number of spaces
string getIndent(int indentSize){
  string indent = "";
  for (int i = 0; i < indentSize; i++){
    indent += " ";
  }
  return indent;
}

//Traverses the filename tree and prints in orderly fashion
void traversePrint(struct Tree f, int indentSize){
  //Print data with number of indents preceding and make recursive call on each of the children
  cout << getIndent(indentSize) << f.data << "\n";
  for (int i = 0; i < f.children.size(); i++){
    traversePrint(f.children[i], indentSize + 2);
  }
}

//Uses helper functions to print all filenames to the user
void PickFile::printFiles(){
  //Print the title and call the recursive file print method
  cout << "\nAll available files and subdirectories in " << PickFile::path << " -> \"" << PickFile::name << "\": \n\n";
  traversePrint(PickFile::files, 0);
}