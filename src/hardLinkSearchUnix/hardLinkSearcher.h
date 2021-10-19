#pragma once

#include <cstdlib>
#include <map>
#include <vector>
#include <dirent.h>

struct IndexNode {
    nlink_t links{};
    std::string path;

    IndexNode() = default;

    IndexNode(const unsigned long &links, std::string path) : links(links), path(std::move(path)) {}
};

class hardLinkSearcher {

private:
    std::map<ino_t, std::vector<IndexNode>> inodeTable;
    std::string rootFolder;

    void searchDirectory(const std::string &path);

    void searchDirCaseDirectory(const std::string &path, const dirent *dirInfo);

    void searchDirCaseRegularFile(const std::string &path, const dirent *dirInfo);

    void analyzeRegularFile(const std::string &path);

    void addNode(ino_t inodeId, nlink_t links, const std::string &path);

public:
    hardLinkSearcher(const std::string &rf = "/");

    void search();

    void printStats() const;
};
