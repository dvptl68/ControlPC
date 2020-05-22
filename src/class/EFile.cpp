#include <iostream>
#include <fstream>
#include <windows.h>
#include "EFile.hpp"

using namespace std;

//Constructor for EFile class
EFile::EFile(int k){
  //Set class key variable
  EFile::key = k;
}

//Encrypts the file at the given path using the key
void EFile::encrypt(string& path){
  //Set random number seed
  srand(EFile::key);
  //Open source file as input stream and temp file as output stream
  ifstream fileIn(path);
  ofstream tempOut("temp.txt");
  //Read each line from file until end is reached
  string p;
  while(getline(fileIn, p)){
    //Iterate through line encrypting each character
		for (int i = 0; i < p.length(); i++){
      p[i] += rand();
    }
    //Add encrypted line to temp file
		tempOut << p << endl;
	}
  //Close all open files
  fileIn.close();
  tempOut.close();
  //Open source file as output stream and temp file as input stream
  ofstream fileOut(path);
  ifstream tempIn("temp.txt");
  //Read each line from temp file until end is reached
  string t;
  while(getline(tempIn, t)){
    //Add encrypted line back to source file
		fileOut << t << endl;
	}
  //Close all open files
  fileOut.close();
  tempIn.close();
  //Delete temp file
  remove("temp.txt");
}

//Decrypts the file at the given path using the key
void EFile::decrypt(string& path){
  //Set random number seed
  srand(EFile::key);
  //Open source file as input stream and temp file as output stream
  ifstream fileIn(path);
  ofstream tempOut("temp.txt");
  //Read each line from file until end is reached
  string p;
  while(getline(fileIn, p)){
    //Iterate through line decrypting each character
		for (int i = 0; i < p.length(); i++){
      p[i] -= rand();
    }
    //Add encrypted line to temp file
		tempOut << p << endl;
	}
  //Close all open files
  fileIn.close();
  tempOut.close();
  //Open source file as output stream and temp file as input stream
  ofstream fileOut(path);
  ifstream tempIn("temp.txt");
  //Read each line from temp file until end is reached
  string t;
  while(getline(tempIn, t)){
    //Add encrypted line back to source file
		fileOut << t << endl;
	}
  //Close all open files
  fileOut.close();
  tempIn.close();
  //Delete temp file
  remove("temp.txt");
}