#include <vector>
#include <string>

using namespace std;

class PickFile{
  private:
    string path;
    vector<string> files;
  public:
    PickFile(string p);
    void printFiles();
};