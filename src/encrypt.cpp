#include <iostream>
#include <windows.h>
#include <map>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "DriveSelect.hpp"
#include "PickFile.hpp"

using namespace std;

int main(){
  //Create class object for drive select
  DriveSelect s;
  //Create map to store drive letters and their names
  map<string, string> drives;
  //Fill map with parsed drive letters and names
  s.parseBuffer(drives);
  //Get drive letter from user
  string d = s.pickDrive(drives);
  if (d.length() > 0){
    //Create class object for file select
    PickFile f(d);
    //Print all available files
    f.printFiles();
  }
}