#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

vector<string> getDrives(){
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
  return drives;
}

string pickDrive(vector<string>& drives){
  if (drives.size() > 0){
    //List all available drives
    cout << "Available drives: \n\n";
    for (int i = 0; i < drives.size(); i++){
      cout << (i+1) << ". " << drives[i] << "\n";
    }
    //Prompt user until a valid drive number is entered
    int index = -1;
    cout << "\nEnter the number for a drive: ";
    cin >> index;
    while (cin.fail() && (index < 1 || index > drives.size())){
      cout << "You must enter a number between 1 and " << drives.size() << "!\n";
      cout << "\nEnter the number for a drive: ";
      cin.clear();
      cin.ignore(256,'\n');
      cin >> index;
    }
    string d = drives[index - 1];
    cout << "You picked: " << d << "\n";
    return d;
  }else{
    cout << "No available drives!";
    return "";
  }
}

int main(){
  vector<string> drives = getDrives();
  pickDrive(drives);
}