#include <Windows.h>
#include <iostream>
#include <map>
#include <cmath>

#define STEP 4096

std::map<unsigned long, unsigned long> fileMap;

void printStats() {
    const int lengthBorder = 1000;

    for (unsigned long i = 0; i < 10; ++i) {
        fileMap[i] = 0;
    }

    unsigned long mFiles = 0;
    for (const auto &interval: fileMap) {
        if (interval.second > mFiles) {
            mFiles = interval.second;
        }
    }

    double scale = mFiles > lengthBorder ? (double) lengthBorder / (double) mFiles : 1.0;
    std::cout << "TABLE: " << std::endl;
    for (const auto &interval: fileMap) {
        auto intSymb = ceil(interval.second * scale);
        printf("[%lu-%lu] File count: %lu->%s\n", interval.first, interval.first + 1, interval.second, std::string(intSymb, '*').c_str());
    }
}

bool isDirectory(DWORD fileAttributes) {
    return (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (!(fileAttributes & FILE_ATTRIBUTE_REPARSE_POINT));
}

void traversal(const std::string &path) {
    WIN32_FIND_DATA FindFileData;
    std::string filepath = path + "*";
    HANDLE hFindFile = FindFirstFile(filepath.c_str(), &FindFileData);
    do {
        if (INVALID_HANDLE_VALUE == hFindFile) {
            std::cout << "Error in finding path: " << path << std::endl;
            std::cout << "Error: " << GetLastError() << std::endl;
            return;
        }

        if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0) {
            continue;
        }

        if (isDirectory(FindFileData.dwFileAttributes)) {
            traversal(path + FindFileData.cFileName + "\\");
            continue;
        }
        unsigned long interval = FindFileData.nFileSizeLow / STEP + 1;
        fileMap[interval]++;
    } while (FindNextFile(hFindFile, &FindFileData));
}

int main() {
    LPCSTR path = R"(C:\Users\Mahomed\)";
    traversal(path);
    printStats();
}
