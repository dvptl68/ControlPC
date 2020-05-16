#include <vector>
#include <string>

using namespace std;

struct Tree {
  string data;
  vector<Tree> children;
};

class GetFile{
  private:
    string path;
    string name;
    struct Tree files;
  public:
    GetFile(string p);
    void printFiles();
};