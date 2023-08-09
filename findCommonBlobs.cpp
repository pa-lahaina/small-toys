#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "inc/cmdlineParser.hpp"

using namespace std;

unordered_map<string, string> filesMap;

void showHelp(void) {
    cout << "findCommonBlobs - Accept two proprietary-files.txt to perform some operations" << endl;
    cout << endl;
    cout << "usage: ./findCommonBlobs [options] <proprietary-files1> <proprietary-files2>" << endl;
    cout << endl;
    cout << "Allowed Options: " << endl;
    cout << "   -h | --help         -   Show this message" << endl;
    cout << "   -i | --inexisted    -   Let the program find the missing parts of file1 relative "
            "to file2"
         << endl;
    cout << "   -d | --duplicated   -   Let the program find the duplicated parts of file1 "
            "relative to file2"
         << endl;
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

string removeRedirect(string s) {
    int pos1 = s.find(":");
    if (pos1 != -1) {
        return s.erase(pos1, s.length() - 1);
    }
    return s;
}

int isSection(string s) {
    int pos1 = s.find("#");
    if (pos1 == 0) {
        return 1;
    }
    return 0;
}

int displayDuplicated(ifstream& file1, ifstream& file2) {
    string s1;

    while (getline(file1, s1)) {
        if (isSection(s1) == 1 || s1.length() == 0) {
            continue;
        }
        s1 = removeMisc(s1);
        s1 = removeRedirect(s1);
        filesMap[s1] = "1";
    }

    while (getline(file2, s1)) {
        s1 = removeMisc(s1);
        s1 = removeRedirect(s1);
        for (const auto& fiterator : filesMap) {
            if (fiterator.first == s1) {
                cout << "duplicated: " << fiterator.first << endl;
            }
        }
    }
    return 0;
}

int displayInexisted(ifstream& file1, ifstream& file2) {
    string s1;

    while (getline(file1, s1)) {
        if (isSection(s1) == 1 || s1.length() == 0) {
            continue;
        }
        s1 = removeMisc(s1);
        s1 = removeRedirect(s1);
        filesMap[s1] = "1";
    }

    while (getline(file2, s1)) {
        s1 = removeMisc(s1);
        s1 = removeRedirect(s1);
        for (const auto& fiterator : filesMap) {
            if (fiterator.first == s1) {
                filesMap[s1] = "2";
            }
        }
    }

    for (const auto& fiterator : filesMap) {
        if (fiterator.second != "2") {
            cout << "inexisted: " << fiterator.first << endl;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    string s1;
    FILE* file;

    try {
        cmdlineParser::parse(argc, argv);
    } catch (const exception& e) {
        cout << "error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    if (cmdlineParser::getHelp() == 1) {
        showHelp();
        return EXIT_SUCCESS;
    }

    ifstream file1(argv[2]);
    ifstream file2(argv[3]);
    if (!file1.is_open() || !file2.is_open()) {
        cout << "File incorrect. Please check your input" << endl;
        showHelp();
        return EXIT_FAILURE;
    }

    if (cmdlineParser::getDup() == 1) {
        displayDuplicated(file1, file2);
    }
    if (cmdlineParser::getInex() == 1) {
        displayInexisted(file1, file2);
    }

    file1.close();
    file2.close();
    return EXIT_SUCCESS;
}
