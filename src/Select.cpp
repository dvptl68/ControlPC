#include <iostream>
#include <algorithm>
#include <windows.h>
#include <map>
#include <string>
#include "Select.hpp"

using namespace std;

Select::Select(void){
  //Fills buffer with drives
  DWORD test = GetLogicalDriveStrings(sizeof(lpBuffer), lpBuffer);
}

void Select::parseBuffer(map<string, string>& drives){
  int i = 0;
  while (i < (sizeof(lpBuffer)-2)){
    //If the format of three consecutive characters is a letter + :\, add to drive map
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

string Select::pickDrive(map<string, string>& drives){
  if (!drives.empty()){
    //List all available drives
    cout << "Available drives: \n\n";
    int i = 0;
    for (const auto& x : drives) {
      i++;
      std::cout << i << ". " << x.first << " -> \"" << x.second << "\"\n";
    }
    //Prompt user to pick a drive by entering letter
    cout << "\nEnter the drive letter: ";
    string letter;
    cin >> letter;
    //Convert to uppercase in case user entered lowercase letter
    transform(letter.begin(), letter.end(), letter.begin(), ::toupper);
    letter += ":\\";
    //Use an iterator to find and print the selected drive from the map
    auto pos = drives.find(letter);
    cout << "You picked: " << pos->first << " - \"" << pos->second << "\"\n";
    return letter;
  }else{
    //Notify the user if the only available drive is the boot drive
    cout << "No available drives!\n";
    return "";
  }
}