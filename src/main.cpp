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
  string password;
  //Check if info file exists
  if (d.infoExists()){
    //If file exists, user has already created password and must verify it
    cout << "Enter the password: ";
    cin >> password;
    if (!d.checkPassword(password)){
      //End program if password is incorrect
      cout << "Wrong password!\n";
      return 0;
    }
  }else{
    //Allow user to create a password
    cout << "Enter a password to be used for file encryption and decryption: ";
    cin >> password;
    d.setPassword(password);
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
  //Allow user to choose whether to encrypt or decrypt files
  int choice;
  cout << "\nEnter 1 to encrypt files or 2 to decrypt files: ";
  cin >> choice;
  if (choice == 1){
    //Create class object for file select and report the time it takes
    cout << "\nParsing file structure...";
    clock_t start = clock();
    GetFile f(dr, true);
    cout << "completed in " << (std::clock() - start) / (double) CLOCKS_PER_SEC << " seconds.";
    //Print all available files
    f.printFiles();
    //Get and print all files that are already encrypted
    vector<string> encrypted = d.getFileInfo(dr);
    //Allow user to select files
    vector<string> files = f.pickEncryptFiles(encrypted);

    //encrypt files

    //Add selected files to info file
    d.addFileInfo(files);
  }else if (choice == 2){
    //Get and print all files that are already encrypted
    vector<string> encrypted = d.getFileInfo(dr);
    //Allow user to select files
    GetFile f(dr, false);
    vector<string> decrypt = f.pickDecryptFiles(encrypted);
  }
}