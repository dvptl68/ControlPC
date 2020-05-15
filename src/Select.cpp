#include <iostream>
#include <algorithm>
#include <windows.h>
#include <map>
#include <string>
#include "Select.hpp"

using namespace std;

//Constructor for Select class
Select::Select(void){
  //Fills buffer with drives
  DWORD test = GetLogicalDriveStrings(sizeof(lpBuffer), lpBuffer);
}

//Parses the character buffer into strings with all drive paths
void Select::parseBuffer(map<string, string>& drives){
  int i = 0;
  while (i < (sizeof(lpBuffer)-2)){
    //If the format of three consecutive characters is a letter + :\, add to drive map
    if (lpBuffer[i+1] == ':' && lpBuffer[i+2] == '\\'){
      char current[4] = {lpBuffer[i], ':', '\\'};
      //Filters out the boot drive
      if (current[0] != 'C'){
        //Gets the name of the drive given the path
        char VolumeName[MAX_PATH];
        GetVolumeInformationA((LPCSTR)current, (LPSTR)VolumeName, sizeof(VolumeName), NULL, NULL, NULL, NULL, 0);
        string letter(current);
        string vol(VolumeName);
        //Add path and drive name as a key-value pair into the map
        drives.insert({letter, vol});
      }
    }
    i++;
  }
}

//Allows the user to pick a drive from the map
string Select::pickDrive(map<string, string>& drives){
  if (!drives.empty()){
    //List all available drives
    cout << "\nAvailable drives: \n\n";
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
    //Use an iterator to find the selected drive from the map
    auto pos = drives.find(letter);
    return letter + (pos->second);
  }else{
    //Notify the user if the only available drive is the boot drive
    cout << "No available drives!\n";
    return "";
  }
}