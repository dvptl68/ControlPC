#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "PickFile.hpp"

using namespace std;

PickFile::PickFile(string p){
  //Set the path private variable
  PickFile::path = p;
  //Fill the file vector with all files in the given drive
  DIR *dir;
  struct dirent *e;
  //Convert the string path into a char array
  const char *path = PickFile::path.c_str();
  if ((dir = opendir(path)) != NULL) {
    while ((e = readdir (dir)) != NULL) {
      PickFile::files.push_back(e->d_name);
    }
    closedir (dir);
  } else {
    //Prints error if drive is removed
    cout << "Error opening drive: " << PickFile::path << "! Make sure it is plugged in and functioning.";
  }
}

void PickFile::printFiles(){
  cout << "\nAll available files and subdirectories: \n\n";
  for(int i=0; i < PickFile::files.size(); i++){
    cout << PickFile::files[i] << "\n";
  }
}