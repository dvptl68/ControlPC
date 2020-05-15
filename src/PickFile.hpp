#include <vector>
#include <string>

using namespace std;

struct Tree {
  string data;
  vector<Tree> children;
};

class PickFile{
  private:
    string path;
    string name;
    struct Tree files;
  public:
    PickFile(string p);
    void printFiles();
};