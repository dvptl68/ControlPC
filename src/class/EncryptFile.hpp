#include <string>

using namespace std;

class EncryptFile {
  private:
    int key;
  public:
    EncryptFile(int k);
    void encrypt(string& path);
    void decrypt(string& path);
};