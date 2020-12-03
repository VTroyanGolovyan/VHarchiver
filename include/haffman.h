#include <iostream>
#include <vector>

/* Read bytes from file */
std::vector<unsigned char> readBytes(std::istream& in);

/* Function for statistic of bytes on file */
std::vector<size_t> getStats(std::vector<unsigned char>& bytes);

/* Get encoded bytes */
std::vector<unsigned char> getEncodedBytes(std::vector<unsigned char>& rawBytes);

/* Save bytes to stream */
void saveBytesToStream(std::ostream& in, std::vector<unsigned char>& bytes);
