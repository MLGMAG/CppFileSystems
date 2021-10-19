#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include "hardLinkSearcher.h"

using namespace std;

void hardLinkSearcher::searchDirCaseDirectory(const string &path, const dirent *dirInfo) {
    string entryName = dirInfo->d_name;

    if (entryName == "." || entryName == "..") {
        return;
    }

    string newSearchPath = path + "/" + entryName;
    if (path == "/") {
        newSearchPath = path + entryName;
    }
    searchDirectory(newSearchPath);
}

void hardLinkSearcher::searchDirCaseRegularFile(const string &path, const dirent *dirInfo) {
    string entryName = dirInfo->d_name;
    string analysisPath = path + "/" + entryName;
    analyzeRegularFile(analysisPath);
}

void hardLinkSearcher::searchDirectory(const string &path) {
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

void hardLinkSearcher::analyzeRegularFile(const string &path) {
    struct stat fileInfo{};
    stat(path.c_str(), &fileInfo);

    if (fileInfo.st_nlink > 1) {
        addNode(fileInfo.st_ino, fileInfo.st_nlink, path);
    }
}

void hardLinkSearcher::addNode(ino_t inodeId, nlink_t links, const string &path) {
    auto node = IndexNode(links, path);
    inodeTable[inodeId].push_back(node);
}

hardLinkSearcher::hardLinkSearcher(const string &rf) : rootFolder(rf) {}

void hardLinkSearcher::search() {
    inodeTable.clear();
    searchDirectory(rootFolder);
}

void hardLinkSearcher::printStats() const {
    for (const auto &it: inodeTable) {
        std::vector<IndexNode> inodeVec = it.second;
        string inodeMessage = "INODE: " + to_string(it.first) + ", LINKS: " + to_string(inodeVec[0].links);
        std::cout << inodeMessage << std::endl;

        for (const IndexNode& inode: inodeVec) {
            string indexNodeMessage = "\t" + inode.path;
            std::cout << indexNodeMessage<< std::endl;
        }
    }
}
