#include <windows.h>
#include <map>
#include <string>
#include "Select.hpp"

using namespace std;

Select::Select(void){
  //Fills buffer with drives
  DWORD test = GetLogicalDriveStrings(sizeof(lpBuffer), lpBuffer);
}

void Select::parseBuffer(map<string, string> drives){
  int i = 0;
  while (i < (sizeof(lpBuffer)-2)){
    //If the format of three consecutive characters is a letter + :\, add to drive vector
    if (lpBuffer[i+1] == ':' && lpBuffer[i+2] == '\\'){
      char current[4] = {lpBuffer[i], ':', '\\'};
      //Filters out the boot drive
      if (current[0] != 'C'){
        char VolumeName[MAX_PATH];
        GetVolumeInformationA((LPCSTR)current, (LPSTR)VolumeName, sizeof(VolumeName), NULL, NULL, NULL, NULL, 0);
        string letter(current);
        string vol(VolumeName);
        drives.insert({letter, vol});
      }
    }
    i++;
  }
}