#include <string>

using namespace std;

class EFile {
  public:
    EFile();
    void encrypt(string& path);
    void decrypt(string& path);
};