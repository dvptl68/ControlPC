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
GetFile::GetFile(string p){
  //Set the path and name private variables
  GetFile::path = p.substr(0, 3);
  GetFile::name = p.substr(3);
  //Initialize the size to 0
  GetFile::size = 0;
  //Set the Tree private variable
  GetFile::files = newTree(GetFile::path + " -> \"" + GetFile::name + "\"");
  //Fill the vector with all available files
  retrieveFiles(GetFile::path, GetFile::files, GetFile::size);
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

//Allows user to pick files, fills a vector with the file paths, and returns the vector
vector<string> GetFile::pickFiles(){
  //Create initial storage variables
  string selected = "a";
  vector<string> paths;
  //Loop executes until nothing is entered
  while (selected != "*"){
    cout << "\nEnter the name of a file (with file extension, case sensitive), or * to quit: ";
    cin >> selected;
    if (selected != "*"){
      //Get path of file using helper method
      string path = findFile(GetFile::files, GetFile::path, selected);
      if (path != ""){
        //Add path to vector if it is valid
        string p = path.substr(0, 3) + path.substr(24);
        cout << "File: " << p << " added to queue.\n";
        paths.push_back(p);
      }else{
        //Warn user if file is not found
        cout << "File: " << selected << " not found!\n";
      }
    }
  }
  return paths;
}

//Prints the currently selected files
void printSelectedFiles(vector<string>& f){
  //List out all file selections
  for (int i = 0; i < f.size(); i++){
    cout << "\n" << (i + 1) << ")" << f[i];
  }
}

//Prompts the user to confirm selections before final stage
void GetFile::confirmFiles(vector<string>& f){
  int selected = 0;
  while (f.size() > 0 && selected != -1){
    //Print current queued files
    printSelectedFiles(f);
    //Prompt user to select a file to remove
    cout << "\n\nEnter the number of the file you would like to remove, or -1 to exit: ";
    cin >> selected;
    if (selected != -1){
      //Delete file and print deleted file name
      string name = f[selected - 1];
      f.erase(f.begin() + selected - 1);
      cout << "\nFile: " << name << " remove from queue.\n";
    }
  }
}