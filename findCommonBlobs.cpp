#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> filesMap;

void showHelp(void) {
    cout << "findCommonBlobs - Accept two proprietary-files.txt to find common part" << endl;
    cout << endl;
    cout << "usage: ./findCommonBlobs <proprietary-files1> <proprietary-files2>" << endl;
}

string removeMisc(string s) {
    int pos1 = s.find("|");
    int pos2 = s.find("-");
    if (pos1 == -1 && pos2 == 0) {
        return s.erase(pos2, 1);
    } else if (pos1 == -1 && pos2 != 0) {
        return s;
    } else if (pos1 != -1 && pos2 != 0) {
        return s.erase(pos1, s.length() - pos1);
    }
    return s.erase(pos1, s.length() - pos1).erase(pos2, 1);
}

int main(int argc, char* argv[]) {
    int j = 0;
    string s1;
    FILE* file;

    if (argc < 3) {
        cout << "Incorrect usage. Make sure you have two pathes in the commandline parameters."
             << endl;
        showHelp();
        return 1;
    }

    ifstream file1(argv[1]);
    ifstream file2(argv[2]);
    if (!file1.is_open() || !file2.is_open()) {
        cout << "File incorrect. Please check your input" << endl;
        return 1;
    }

    while (file1 >> s1) {
        s1 = removeMisc(s1);
        filesMap[s1] = "1";
    }

    while (file2 >> s1) {
        s1 = removeMisc(s1);
        for (const auto& fiterator : filesMap) {
            if (fiterator.first == s1) {
                cout << "duplicated: " << fiterator.first << endl;
                j++;
            }
        }
    }

    cout << "duplicated count: " << j << endl;

    file1.close();
    file2.close();
    return 0;
}