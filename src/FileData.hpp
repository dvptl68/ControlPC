#include <string>

using namespace std;

class FileData {
  private:
    string masterPassword;
  public:
    FileData();
    void userInfo();
    void encryptionInfo();
};