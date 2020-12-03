#include <iostream>
#include <vector>

std::vector<unsigned char> readBytes(std::istream& in) {
    std::vector<unsigned char> result;
    unsigned char byte;
    while (in >> byte) {
        result.emplace_back(byte);
    }
    return result;
}

std::vector<size_t> getStats(std::vector<unsigned char>& bytes) {
    std::vector <size_t> result(255, 0);
    for (unsigned char byte : bytes) {
        ++result[byte];
    }
    return result;
}

std::vector<unsigned char> getEncodedBytes(std::vector<unsigned char>& rawBytes) {
    return rawBytes;
}

void saveBytesToStream(std::ostream& out, std::vector<unsigned char>& bytes) {
    for (unsigned char byte : bytes) {
        out << byte;
    }
}
