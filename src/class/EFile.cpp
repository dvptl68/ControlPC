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
	char ch;
	fstream file, fileTemp;
	file.open(path);
	if(!file){
		cout<<"Error opening file!";
	}
	fileTemp.open("temp.txt");
	if(!fileTemp){
		cout<<"Error creating temp file!";
		file.close();
	}
	while(file.eof()==0){
		file>>ch;
		ch=ch+100;
		fileTemp<<ch;
	}
	file.close();
	fileTemp.close();
	file.open(path);
	if(!file){
		cout<<"Error opening source file!";
	}
	fileTemp.open("temp.txt");
	if(!fileTemp){
		cout<<"Error in opening temp.txt file...!!";
		file.close();
	}
	while(fileTemp.eof()==0){
		fileTemp>>ch;
		file<<ch;
	}
	cout<<"File "<<path<<" encrypted successfully..!!";
	cout<<"\nPress any key to exit...";
}

//Decrypts the file at the given path using the key
void EFile::decrypt(string& path){

}