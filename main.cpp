#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <haffman.h>
#include <HaffmanTree.h>


int main(int argc, char** argv) {

    std::string file_to_encode(argv[1]);
    std::string file_to_save(argv[2]);

    std::ifstream in(file_to_encode);
    auto bytes = readBytes(in);
    auto stats = getStats(bytes);

    HaffmanTree* tree = new HaffmanTree();
    tree->buildTree(stats);

    std::ofstream out(file_to_save);
    saveBytesToStream(out, bytes);

    return 0;

}
