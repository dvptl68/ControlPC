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
  Tree t;
  t.data = d;
  return t;
}

void retrieveFiles(string& p, struct Tree& files){
  DIR *dir;
  struct dirent *e;
  const char *path = p.c_str();
  if ((dir = opendir(path)) != NULL) {
    vector<Tree> c;
    while ((e = readdir(dir)) != NULL) {
      c.push_back(newTree(e->d_name));
    }
    files.children = c;
    closedir (dir);
  }
}

PickFile::PickFile(string p){
  //Set the path private variable
  PickFile::path = p.substr(0, 3);
  PickFile::name = p.substr(3);
  PickFile::files = newTree(PickFile::path + " -> \"" + PickFile::name + "\"");
  //Fill the vector with all available files
  retrieveFiles(PickFile::path, PickFile::files);
}

string getIndent(int indentSize){
  string indent = "";
  for (int i = 0; i < indentSize; i++){
    indent += " ";
  }
  return indent;
}

void traversePrint(struct Tree f, int indentSize){
  cout << getIndent(indentSize) << f.data << "\n";
  for (int i = 0; i < f.children.size(); i++){
    traversePrint(f.children[i], indentSize + 2);
  }
}

void PickFile::printFiles(){
  cout << "\nAll available files and subdirectories in " << PickFile::path << " -> \"" << PickFile::name << "\": \n\n";
  traversePrint(PickFile::files, 0);
}