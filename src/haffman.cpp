#include <iostream>
#include <vector>
#include <map>
#include "haffman.h"

std::vector<unsigned char> readBytes(std::istream& in) {
    std::vector<unsigned char> result;
    while (!in.fail()) {
        unsigned char byte;
        byte = in.get();
        if (byte != EOF) {
            result.push_back(byte);
        }
    }
    result.pop_back();
    return result;
}

std::vector<size_t> getStats(std::vector<unsigned char>& bytes) {
    std::vector <size_t> result(256, 0);
    for (unsigned char byte : bytes) {
        ++result[byte];
    }
    return result;
}

std::vector<size_t> decodeStats(std::vector<unsigned char>& bytes) {

    void* raw_data = reinterpret_cast<void*>(bytes.data());

    std::vector<size_t> stats;

    for (size_t i = 0; i < 257; ++i) {
        stats.push_back(*(reinterpret_cast<size_t*>(raw_data) + i));
    }

    return stats;

}

std::vector<unsigned char> getEncodedBytes(std::vector<unsigned char>& rawBytes) {
    return rawBytes;
}

void saveBytesToStream(std::ostream& out, std::vector<unsigned char>& bytes) {
    for (unsigned char byte : bytes) {
        out.put(byte);
    }
}

unsigned char getByte(const std::string& byte_str) {
    int i = 0;
    unsigned char result = 0;
    for (auto& ch : byte_str) {
        if (ch == '1') {
            result |= (1 << (7 - i));
        }
        ++i;
    }
    return result;
}

void saveBytes(
    std::vector<unsigned char>& bytes,
    void* bytes_arr,
    size_t n
) {
    for (size_t i = 0; i < n; ++i) {
        unsigned char byte = *(reinterpret_cast<unsigned char*>(bytes_arr) + i);
        bytes.push_back(byte);
    }
}

void saveStatistics(
    std::vector<unsigned char>& bytes,
    std::vector<size_t>& stats
) {
    for (auto& cnt : stats) {
        saveBytes(bytes, &cnt, sizeof(size_t));
    }
}

std::vector<unsigned char> encodeBytes(
    std::vector<size_t>& stats,
    std::map<unsigned char, std::string>& dictionary,
    std::vector<unsigned char>& bytes
) {

    std::vector<unsigned char> new_bytes;
    /* we need to build Haffman Tree again */
    saveStatistics(new_bytes, stats);

    std::string temp_result;

    std::vector<unsigned char> code_bytes;
    size_t bits_count = 0;
    for (auto& byte : bytes) {
        std::cout << (char)byte << " " << dictionary[byte] << std::endl;
        temp_result += dictionary[byte];
        bits_count += dictionary[byte].length();
        if (temp_result.length() >= 8) {
            code_bytes.push_back(getByte(temp_result.substr(0, 8)));
            std::cout << temp_result.substr(0, 8);
            temp_result = temp_result.substr(8);
        }
    }
    if (temp_result.length() > 0) {
        code_bytes.push_back(
            getByte(
                temp_result.substr(0, temp_result.length()) + std::string(8 - temp_result.length(), '0')
            )
        );
    }
    /* we need to know bits count */
    saveBytes(
        new_bytes,
        &bits_count,
        sizeof(size_t)
    );
    /* bits */
    for (auto& byte : code_bytes) {
        new_bytes.push_back(byte);
    }

    return new_bytes;

}

std::vector<unsigned char> decodeBytes(
    HaffmanTree* tree,
    std::vector<unsigned char>& bytes,
    size_t all_bits
) {
    std::vector<unsigned char> result;
    size_t i = 257 * sizeof(size_t) * 8;
    size_t end = i + all_bits;
    std::cout << i << " " << end << " " << all_bits << std::endl;
    for (; i < end;) {
        unsigned char ch = tree->iterateSymbol(bytes, i);
        std::cout << ch;
        result.push_back(ch);
    }

    return result;
}
