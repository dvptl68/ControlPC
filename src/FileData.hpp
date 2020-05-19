#include <fstream>
#include <string>

using namespace std;

class FileData {
  private:
    string masterPassword;
    int masterKey;
  public:
    FileData();
    bool infoExists();
    void setPassword(string p);
    bool checkPassword(string p);
};