#include <string>
#include <dirent.h>
#include <cmath>
#include "directoryTraverser.h"

int main(int argc, char **argv) {

    std::string root;
    unsigned long step;
    if (argc == 3) {
        root = std::string(argv[1]);
        step = strtoul(argv[2], nullptr, 10);
    } else {
        root = "/";
        step = 1024;
    }

    DirectoryTraverser dirTraverser(root, step);
    dirTraverser.traverse();
    dirTraverser.printStats();

    return 0;
}
