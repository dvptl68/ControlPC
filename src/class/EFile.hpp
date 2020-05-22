#include <string>

using namespace std;

class EFile {
  public:
    EFile();
    void encrypt(string& path, int& key);
    void decrypt(string& path, int& key);
};