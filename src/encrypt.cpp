#include <iostream>
#include <algorithm>
#include <windows.h>
#include <map>
#include <string>
#include "Select.hpp"

using namespace std;

string pickDrive(map<string, string>& drives){
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

int main(){
  // map<string, string> drives = getDrives();
  Select s;
  map<string, string> drives;
  s.parseBuffer(drives);
  string d = pickDrive(drives);
}