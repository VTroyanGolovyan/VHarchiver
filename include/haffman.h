#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "HaffmanTree.h"
/* Read bytes from file */
std::vector<unsigned char> readBytes(std::istream& in);

/* Function for statistic of bytes on file */
std::vector<size_t> getStats(std::vector<unsigned char>& bytes);

/* Function for statistic of bytes on encoded file */
std::vector<size_t> decodeStats(std::vector<unsigned char>& bytes);

/* Get encoded bytes */
std::vector<unsigned char> getEncodedBytes(std::vector<unsigned char>& rawBytes);

/* Save bytes to stream */
void saveBytesToStream(std::ostream& in, std::vector<unsigned char>& bytes);

/* get byte by string view */
unsigned char getByte(const std::string& byte_str);

/* Encode bytes */
std::vector<unsigned char> encodeBytes(
    std::vector<size_t>& stats,
    std::map<unsigned char, std::string>& dictionary,
    std::vector<unsigned char>& bytes
);

/* Decode bytes */
std::vector<unsigned char> decodeBytes(
    HaffmanTree*,
    std::vector<unsigned char>& bytes,
    size_t all_bits
);
