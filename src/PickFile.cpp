#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "PickFile.hpp"

using namespace std;

struct Tree {
  string data;
  vector<Tree> children;
  void setData(string d){
    data = d;
  }
  void setChildren(vector<Tree> c){
    children = c;
  }
};

void retrieveFiles(string& p, struct Tree files){
  DIR *dir;
  struct dirent *e;
  vector<string> children;
  const char *path = p.c_str();
  if ((dir = opendir (path)) != NULL) {
    while ((e = readdir (dir)) != NULL) {
      children.push_back(e->d_name);
    }
  }else{
    cout << "Not a directory.";
  }
  closedir (dir);
}

PickFile::PickFile(string p){
  //Set the path private variable
  PickFile::path = p.substr(0, 3);
  PickFile::name = p.substr(3);
  struct Tree t;
  PickFile::files = t;
  //Fill the vector with all available files
  retrieveFiles(PickFile::path, PickFile::files);
}

void PickFile::printFiles(){
  cout << "\nAll available files and subdirectories in " << PickFile::path << " -> \"" << PickFile::name << "\": \n\n";
  //change to account for tree file structure
  // for(int i=0; i < PickFile::files.size(); i++){
  //   cout << PickFile::files[i] << "\n";
  // }
}