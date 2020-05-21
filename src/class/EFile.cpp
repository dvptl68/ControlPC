#include <iostream>
#include <fstream>
#include <windows.h>
#include "EFile.hpp"

using namespace std;

//Constructor for EFile class
EFile::EFile(int k){
  //Set private key variable
  EFile::key = k;
}

//Encrypts the file at the given path using the key
void EFile::encrypt(string& path){

}

//Decrypts the file at the given path using the key
void EFile::decrypt(string& path){

}