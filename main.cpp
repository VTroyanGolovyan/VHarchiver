#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <haffman.h>

int main(int argc, char** argv) {

    if (argc <= 1) {

        std::cout << "Error, please use --encode/--decode flags." << std::endl;
        std::cout << "You can use --help for details." << std::endl;

    }

    std::string mode(argv[1]);

    if (mode == "--encode") {

        std::string file_to_encode(argv[2]);
        std::string file_to_save(argv[3]);

        std::ifstream in(file_to_encode);
        auto bytes = readBytes(in);
        in.close();

        auto stats = getStats(bytes);

        auto* tree = new HaffmanTree();
        tree->buildTree(stats);

        auto dict = tree->getDict();
        delete tree;

        auto new_bytes = encodeBytes(stats, dict, bytes);

        std::ofstream out(file_to_save);
        saveBytesToStream(out, new_bytes);
        out.close();

    } else if (mode == "--decode"){

        std::string file_to_decode(argv[2]);
        std::string file_to_save(argv[3]);

        std::ifstream in(file_to_decode);
        auto bytes = readBytes(in);
        auto stats = decodeStats(bytes);
        std::vector<size_t> r_stat(stats.begin(), stats.end() - 1);
        auto* tree = new HaffmanTree();
        tree->buildTree(r_stat);

        auto decoded_bytes = decodeBytes(tree, bytes, stats[256]);
        delete tree;

        std::ofstream out(file_to_save);
        saveBytesToStream(out, decoded_bytes);
        out.close();

    } else if (mode == "--help") {

        std::cout << "Compress file:" << std::endl;
        std::cout << "vh-compress --encode <source> <result>" << std::endl;
        std::cout << "Extract file:" << std::endl;
        std::cout << "vh-compress --decode <source> <result>" << std::endl;

    } else {

        std::cout << "Error, please use --encode/--decode flags." << std::endl;
        std::cout << "You can use --help for details." << std::endl;

    }

    return 0;

}
