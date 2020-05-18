#include <fstream>
#include <string>

using namespace std;

class FileData {
  private:
    string masterPassword;
    int masterKey;
    fstream info;
  public:
    FileData();
    bool infoExists();
    void setPassword();
    bool checkPassword(string p);
};