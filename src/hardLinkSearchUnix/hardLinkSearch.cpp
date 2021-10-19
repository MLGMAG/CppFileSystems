#include <string>
#include "hardLinkSearcher.h"

int main(int argc, char **argv) {

    std::string root;
    if (argc == 2) {
        root = std::string(argv[1]);
    } else {
        root = "/";
    }

    hardLinkSearcher searcher(root);
    searcher.search();
    searcher.printStats();

    return 0;
}
