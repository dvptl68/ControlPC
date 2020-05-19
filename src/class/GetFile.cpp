#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "GetFile.hpp"

using namespace std;

//Utility function to get a new tree
Tree newTree(string d){
  //Create a new tree, set the data, and return the tree
  Tree t;
  t.data = d;
  return t;
}

//Traverses all the files on the drive and places filenames in tree structure
void retrieveFiles(string& p, struct Tree& files, int& size){
  DIR *dir;
  struct dirent *e;
  //Convert the path into a char array
  const char *path = p.c_str();
  //Test if the given path is a directory
  if ((dir = opendir(path)) != NULL) {
    //Add a backslash to show that it is a directory
    files.data += "\\";
    //Populate the vector with filenames
    while ((e = readdir(dir)) != NULL) {
      string name = e->d_name;
      //Filter out unecessary files/directories
      if (name != "." && name != ".." && name != "System Volume Information" && (name.length() > 3 && name.substr(name.length()-4) != ".zip")){
        //Add file/directory to children vector and increase total size
        files.children.push_back(newTree(name));
        size++;
      }
    }
    closedir (dir);
    //Recursively call retrieveFiles on each child to fill subdirectories
    for (int i = 0; i < files.children.size(); i++){
      string path = p + files.children[i].data + "\\";
      retrieveFiles(path, files.children[i], size);
    }
  }
}

//Constructor for PickFile class
GetFile::GetFile(string p, bool encrypt){
  //Set the path and name private variables
  GetFile::path = p.substr(0, 3);
  GetFile::name = p.substr(3);
  //Initialize the size to 0
  GetFile::size = 0;
  //Set the Tree private variable
  GetFile::files = newTree(GetFile::path + " -> \"" + GetFile::name + "\"");
  if (encrypt){
    //Fill the vector with all available files
    retrieveFiles(GetFile::path, GetFile::files, GetFile::size);
  }
}

//Returns a string with indentSize number of spaces
string getIndent(int indentSize){
  string indent = "";
  if (indentSize > 0){
    //Add spaces and vertical lines
    for (int i = 0; i < indentSize - 2; i++){
      if (i % 3 == 0){
        indent += "|";
      }else{
        indent += " ";
      }
    }
    //Add dashes leading up to the file name
    for (int i = 0; i < 2; i++){
      indent += "-";
    }
  }
  return indent;
}

//Traverses the filename tree and prints in orderly fashion
void traversePrint(struct Tree& f, int indentSize){
  //Print data with number of indents preceding and make recursive call on each of the children
  cout << getIndent(indentSize) << f.data << "\n";
  for (int i = 0; i < f.children.size(); i++){
    traversePrint(f.children[i], indentSize + 3);
  }
}

//Uses helper functions to print all filenames to the user
void GetFile::printFiles(){
  if (GetFile::size > 0){
    //Print the number of files and call the recursive file print method
    cout << "\n" << GetFile::size << " available files: \n\n";
    traversePrint(GetFile::files, 0);
  }else{
    //Notify the user that there are no available files
    cout << "\nDrive " << GetFile::files.data.substr(0, GetFile::files.data.length()-1) << " has no available files!\n";
  }
}

//Returns whether the given vector contains the given string
bool containsStr(vector<string>& v, string& s){
  bool contains = false;
  for (int i = 0; i < v.size() && !contains; i++){
    contains |= (v[i] == s);
  }
  return contains;
}

//Recursive file search algorithm
string findFile(struct Tree& files, string path, string& fileName){
  //Initial return value is an empty string
  string r = "";
  if (files.children.size() == 0 && files.data == fileName){
    //If file is found, fileName is appended to the path
    r =  path + fileName;
  }else{
    //If file is not found, the children of the tree are searched
    for (int i = 0; i < files.children.size() && r == ""; i++){
      r = findFile(files.children[i], path + files.data, fileName);
    }
  }
  return r;
}

//Prints the currently selected files
void printSelectedFiles(vector<string>& f){
  //List out all file selections
  cout << "\nQueued files: ";
  for (int i = 0; i < f.size(); i++){
    cout << "\n" << (i + 1) << ")" << f[i];
  }
}

//Allows user to pick files to encrypt, fills a vector with the file paths, and returns the vector
vector<string> GetFile::pickEncryptFiles(vector<string>& encrypted){
  //Create initial storage variables
  string selected = "a";
  vector<string> paths;
  //Loop executes until nothing is entered
  while (selected != "*"){
    cout << "\nEnter the name of a file to encrypt (with file extension, case sensitive), or * to start encryption: ";
    cin >> selected;
    if (selected != "*"){
      //Get path of file using helper method
      string path = findFile(GetFile::files, GetFile::path, selected);
      if (path != ""){
        //Add path to vector if it is valid
        string p = path.substr(0, 3) + path.substr(24);
        if (!containsStr(encrypted, p)){
          if (!containsStr(paths, p)){
            cout << "File: " << p << " added to queue.\n";
            paths.push_back(p);
          }else{
            //Warn user if file has already been selected
            cout << "File: " << p << " is already in queue!\n";
          }
        }else{
          //Warn user if file is already encrypted
          cout << "File: " << p << " is already encrypted!\n";
        }
      }else{
        //Warn user if file is not found
        cout << "File: " << selected << " not found!\n";
      }
    }
  }
  return paths;
}

//Allows user to pick files to decrypt and returns a vector with the chosen file paths
vector<string> GetFile::pickDecryptFiles(vector<string>& encrypted){
  int selected = 0;
  vector<string> decrypt;
  while (encrypted.size() > 0 && selected != -1){
    //Prompt user to select a file to remove
    cout << "\nEnter the number of the file you would like to decrypt, or -1 to begin decryption: ";
    cin >> selected;
    if (selected != -1){
      if (selected < 1 || selected > encrypted.size()){
        //Warn user if the number is out of range
        cout << "You must enter a number between 1 and " << encrypted.size() << "!\n";
      }else{
        if (containsStr(decrypt, encrypted[selected - 1])){
          //Warn user if file has already been selected
          cout << "File: " << encrypted[selected - 1] << " is already in queue!\n";
        }else{
          //Add selected file to decryption vector
          decrypt.push_back(encrypted[selected - 1]);
          cout << "File: " << encrypted[selected - 1] << " added to queue.\n";
        }
      }
    }
  }
  return decrypt;
}