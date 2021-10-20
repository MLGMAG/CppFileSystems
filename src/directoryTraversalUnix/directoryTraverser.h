#pragma once

#include <map>

class DirectoryTraverser {
private:
    std::string rootFolder = "/";
    unsigned long step = 1024;
    std::map<unsigned long, unsigned long> fileMap;

    void searchDirectory(const std::string &path);

    void searchDirCaseDirectory(const std::string &path, const dirent *dirInfo);

    void searchDirCaseRegularFile(const std::string &path, const dirent *dirInfo);

    void addFile(const std::string &path);

public:

    DirectoryTraverser();

    DirectoryTraverser(const std::string &rootFolder, const unsigned long &step);

    void traverse();

    void printStats();
};
