#include <string>

using namespace std;

class EFile {
  private:
    int key;
  public:
    EFile(int k);
    void encrypt(string& path);
    void decrypt(string& path);
};