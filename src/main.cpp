#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include "DriveSelect.hpp"
#include "GetFile.hpp"
#include "FileData.hpp"

using namespace std;

int main(){
  //Create file for information storage
  FileData d;
  if (d.infoExists()){
    cout << "exists";
  }else{
    cout << "doesn't exist";
  }
  //Create class object for drive select
  DriveSelect s;
  //Create map to store drive letters and their names
  map<string, string> drives;
  //Fill map with parsed drive letters and names
  s.parseBuffer(drives);
  //Get drive letter from user
  string dr = s.pickDrive(drives);
  //End program if there are no available drives
  if (dr.length() == 0){ return 0; }
  //Create class object for file select and report the time it takes
  cout << "\nParsing file structure...";
  clock_t start = clock();
  GetFile f(dr);
  cout << "completed in " << (std::clock() - start) / (double) CLOCKS_PER_SEC << " seconds.";
  //Print all available files
  f.printFiles();
  //Allow user to select files
  vector<string> files = f.pickFiles();
  //Prompt user to confirm selections
  f.confirmFiles(files);
}