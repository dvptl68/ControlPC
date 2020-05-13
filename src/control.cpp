#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

int main(){
  //Buffer for drives
  char lpBuffer[30];
  //Fills buffer with drives
  DWORD test = GetLogicalDriveStrings( sizeof(lpBuffer), lpBuffer);
  //Parse buffer contents into a vector of drive names
  vector<string> drives;
  int i = 0;
  while (i < (sizeof(lpBuffer)-2)){
    //If the format of three consecutive characters is a letter + :\, add to drive vector
    if (lpBuffer[i+1] == ':' && lpBuffer[i+2] == '\\'){
      string current = "";
      current += lpBuffer[i];
      current += lpBuffer[i+1];
      current += lpBuffer[i+2];
      //Filters out the boot drive
      if (current != "C:\\"){
        drives.push_back(current);
      }
    }
    i++;
  }
  for (int i = 0; i < drives.size(); i++){
    cout << drives[i] << ", ";
  }
}