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
  if (!fileOut){ cout << "Error opening source file\n"; }
  ofstream tempIn("temp.txt");
  if (!tempIn){ cout << "Error creating temp file\n";}
  char ch;
  while(fileOut.eof()==0){
		fileOut>>ch;
		ch=ch+100;
		tempIn<<ch;
	}
  fileOut.close();
  tempIn.close();
}

//Decrypts the file at the given path using the key
void EFile::decrypt(string& path){

}