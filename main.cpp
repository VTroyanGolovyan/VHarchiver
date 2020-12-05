#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <haffman.h>
#include <HaffmanTree.h>


int main(int argc, char** argv) {

    std::string mode(argv[1]);

    if (mode == "-encode") {

        std::string file_to_encode(argv[2]);
        std::string file_to_save(argv[3]);

        std::ifstream in(file_to_encode);
        auto bytes = readBytes(in);
        in.close();

        auto stats = getStats(bytes);

        HaffmanTree* tree = new HaffmanTree();
        tree->buildTree(stats);

        auto dict = tree->getDict();

        auto new_bytes = encodeBytes(stats, dict, bytes);

        std::ofstream out(file_to_save);
        saveBytesToStream(out, new_bytes);
        out.close();

    } else {

        std::string file_to_decode(argv[2]);
        std::string file_to_save(argv[3]);

        std::ifstream in(file_to_decode);
        auto bytes = readBytes(in);
        auto stats = decodeStats(bytes);

    }

    return 0;

}
