#include <map>
#include <string>

using namespace std;

class Select{
  private:
    char lpBuffer[30];
  public:
    Select();
    void parseBuffer(map<string, string>& drives);
    string pickDrive(map<string, string>& drives);
};