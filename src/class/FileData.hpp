#include <fstream>
#include <vector>
#include <string>

using namespace std;

class FileData {
  private:
    string password;
    int passKey;
    int infoKey;
    string path;
  public:
    FileData(string& p);
    bool infoExists();
    void setPassword(string p);
    bool checkPassword(string p);
    void addFileInfo(vector<string>& f);
    void removeFileInfo(vector<string>& encrypted, vector<string>& decrypted);
    vector<string> getFileInfo(string& drive);
};