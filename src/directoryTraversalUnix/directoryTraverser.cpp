#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <cmath>
#include "directoryTraverser.h"

using namespace std;

string getEntryPath(const string &path, const string &entryName) {
    string newSearchPath = path + "/" + entryName;

    if (path == "/") {
        newSearchPath = path + entryName;
    }

    return newSearchPath;
}

void DirectoryTraverser::searchDirectory(const std::string &path) {
    DIR *dir = opendir(path.c_str());

    if (!dir) {
        string errorMessage = "ERROR OPENING DIRECTORY: PATH [" + path + "]";
        cout << errorMessage << std::endl;
        return;
    }

    const dirent *dirInfo = readdir(dir);
    while (dirInfo) {
        switch (dirInfo->d_type) {
            case DT_DIR:
                searchDirCaseDirectory(path, dirInfo);
                break;
            case DT_REG:
                searchDirCaseRegularFile(path, dirInfo);
                break;
            default:
                break;
        }
        dirInfo = readdir(dir);
    }

    closedir(dir);
}

void DirectoryTraverser::searchDirCaseDirectory(const string &path, const dirent *dirInfo) {
    string entryName = dirInfo->d_name;

    if (entryName == "." || entryName == "..") {
        return;
    }

    string newSearchPath = getEntryPath(path, entryName);
    searchDirectory(newSearchPath);
}

void DirectoryTraverser::searchDirCaseRegularFile(const string &path, const dirent *dirInfo) {
    string entryName = dirInfo->d_name;
    string entryPath = getEntryPath(path, entryName);
    addFile(entryPath);
}

void DirectoryTraverser::addFile(const std::string &path) {
    struct stat fileInfo{};
    stat(path.c_str(), &fileInfo);
    unsigned long interval = fileInfo.st_size / step + 1;

    fileMap[interval]++;
}

DirectoryTraverser::DirectoryTraverser() = default;

DirectoryTraverser::DirectoryTraverser(const std::string &rootFolder, const unsigned long &step)
        : rootFolder(rootFolder), step(step) {}

void DirectoryTraverser::traverse() {
    fileMap.clear();
    searchDirectory(rootFolder);
}

void DirectoryTraverser::printStats() {
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
