#include <iostream>
#include <windows.h>
#include <map>
#include <string>
#include "Select.hpp"

using namespace std;

int main(){
  Select s;
  map<string, string> drives;
  s.parseBuffer(drives);
  string d = s.pickDrive(drives);
}