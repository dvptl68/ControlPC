#include <iostream>
#include <windows.h>
#include <map>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "Select.hpp"

using namespace std;

int main(){
  Select s;
  //Create map to store drive letters and their names
  map<string, string> drives;
  //Fill map with parsed drive letters and names
  s.parseBuffer(drives);
  //Get drive letter from user
  string d = s.pickDrive(drives);
  
  DIR *dir;
  struct dirent *ent;
  const char *path = d.c_str();
  if ((dir = opendir(path)) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      printf ("%s\n", ent->d_name);
    }
    closedir (dir);
  } else {
    perror ("Error opening drive! Make sure it is plugged in and functioning.");
  }
}