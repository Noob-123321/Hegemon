#include <fstream>

int extract_bit(const char* filename, int bit_index) {

    int byte_index = bit_index / 8;
    int bit_offset = bit_index % 8;

    std::ifstream file(filename, std::ios::binary);

    file.seekg(byte_index);
    char byte;
    if (!file.read(&byte, 1)) return -1;

    return (byte >> bit_offset) & 1;
}

