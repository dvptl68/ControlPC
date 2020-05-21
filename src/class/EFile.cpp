#include <iostream>
#include <fstream>
#include <windows.h>
#include "EFile.hpp"

using namespace std;

//Constructor for EFile class
EFile::EFile(void){
  //Nothing to do here
}

//Encrypts the file at the given path using the key
void EFile::encrypt(string& path){
  ifstream fileOut(path);
  ofstream tempIn("temp.txt");
  string p;
  while(getline(fileOut, p)){
    string temp;
		for (int i = 0; i < p.length(); i++){
      temp.push_back(p[i]+1);
    }
		tempIn << temp << endl;
	}
  fileOut.close();
  tempIn.close();
  remove("temp.txt");
}

//Decrypts the file at the given path using the key
void EFile::decrypt(string& path){
}