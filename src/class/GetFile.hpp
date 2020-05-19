#include <vector>
#include <string>

using namespace std;

struct Tree {
  string data;
  vector<Tree> children;
};

class GetFile {
  private:
    string path;
    string name;
    int size;
    struct Tree files;
  public:
    GetFile(string p, bool encrypt);
    void printFiles();
    vector<string> pickEncryptFiles(vector<string>& encrypted);
    vector<string> pickDecryptFiles(vector<string>& encrypted);
};