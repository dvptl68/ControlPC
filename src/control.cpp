#include <iostream>
#include <windows.h>

using std::cout;
using std::system;

char lpBuffer[30];// buffer for drive string storage
int main(){
  DWORD test = GetLogicalDriveStrings( sizeof(lpBuffer), lpBuffer);
  for(int i = 0; i<sizeof(lpBuffer); i++){
    cout << lpBuffer[i];
  }
  return 0;
}