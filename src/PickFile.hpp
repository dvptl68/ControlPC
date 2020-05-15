#include <vector>
#include <string>

using namespace std;

class PickFile{
  private:
    string path;
    string name;
    // vector<string> files;
    struct Tree files;
  public:
    PickFile(string p);
    void printFiles();
};