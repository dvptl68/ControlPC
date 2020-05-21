#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include "class/DriveSelect.hpp"
#include "class/GetFile.hpp"
#include "class/FileData.hpp"
#include "class/EFile.hpp"

using namespace std;

//Verifies the user
bool verify(FileData& d, string& dr){

  string password;

  //Check if info file exists
  if (d.infoExists()){

    //If file exists, user has already created password and must verify it
    cout << "\nEnter the password for " << dr.substr(0, 3) << " -> \"" << dr.substr(3)<< "\": ";
    cin >> password;

    if (!d.checkPassword(password)){

      //End program if password is incorrect
      cout << "Wrong password!\n";
      return false;
    }

  }else{

    //Allow user to create a password
    cout << "\nEnter a password to be used for file encryption and decryption for " << dr.substr(0, 3) << " -> \"" << dr.substr(3)<< "\": ";
    cin >> password;
    d.setPassword(password);
    cout << "\nThis program will create a file called \"info\" in the selected drive. DO NOT delete or edit this file, or you will lose the ability to decrypt your files.\n";
    cout << "Press any key to continue...\n";
    getch();
  }

  return true;
}

//Allows user to select a drive
string pickDrive(){

  //Create class object for drive select
  DriveSelect s;

  //Create map to store drive letters and their names
  map<string, string> drives;

  //Fill map with parsed drive letters and names
  s.parseBuffer(drives);

  //Get drive letter from user
  return s.pickDrive(drives);
}

//Driver function if encrypt is selected
void encryptSelected (FileData& d, EFile& e, string& dr){

  //Create class object for file select and report the time it takes
  cout << "\nParsing file structure...";
  clock_t start = clock();
  GetFile f(dr, true);
  cout << "completed in " << (std::clock() - start) / (double) CLOCKS_PER_SEC << " seconds.";

  //Print all available files
  f.printFiles();

  //Get and print all files that are already encrypted
  vector<string> encrypted = d.getFileInfo(dr);

  //Allow user to select files to encrypt
  vector<string> files = f.pickEncryptFiles(encrypted);

  //Iterate through files vector, encrypting each file
  for (int i = 0; i < files.size(); i++){
    e.encrypt(files[i]);
  }

  //Add selected files to info file
  d.addFileInfo(files);
}

//Driver function if decrypt is selected
void decryptSelected(FileData& d, EFile& e, string& dr){

  //Get and print all files that are already encrypted
  vector<string> encrypted = d.getFileInfo(dr);

  //Allow user to select files to decrypt
  GetFile f(dr, false);
  vector<string> decrypt = f.pickDecryptFiles(encrypted);

  //Iterate through decrypt vector, decrypting each file
  for (int i = 0; i < decrypt.size(); i++){
    e.decrypt(decrypt[i]);
  }

  //Remove decrypted files from info file
  d.removeFileInfo(encrypted, decrypt);
}

int main(){

  //Get a drive path from user
  string dr = pickDrive();
  //End program if there are no available drives
  if (dr.length() == 0) { return 0; }

  //Create file for information storage
  FileData d(dr);
  //End the program if user verification fails
  if (!verify(d, dr)) { return 0; }

  //Allow user to choose whether to encrypt or decrypt files
  int choice;
  cout << "\nEnter 1 to encrypt files or 2 to decrypt files: ";
  cin >> choice;

  //Create object for file encryption/decryption
  EFile e;

  //Calls the appropriate driver function based on user selection
  if (choice == 1) { encryptSelected(d, e, dr); }else if (choice == 2) { decryptSelected(d, e, dr); } else { return 0; }
}
