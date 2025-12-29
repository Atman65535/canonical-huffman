//
// Created by atman on 12/25/25.
//

#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "priority_queue.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::shared_ptr;

/**
 * write bit. IO class.
 */
class BitReader {
private:
    ifstream& file_in;
    uint64_t read_buf = 0;
    uint8_t bit_counter = 0;

public:
    explicit BitReader(ifstream& in_file) : file_in(in_file) {
    }

    /**
     * usage : for i in range(min len, max len+1):
     *              peek; remove_code if matched, else continue.
     * @param len len of code. from shortest to longest.
     * @return the code of this length.
     */
    uint32_t peek_code_with_len(const uint8_t len) {
        if (bit_counter < 32)
            read_file();
        const uint32_t ret = read_buf >> (64 - len);
        return ret;
    }
    void remove_code(const uint8_t len) {
        read_buf <<= len;
        bit_counter -= len;
    }
private:
    /**
     * this function read 4 byte at once.
     */
    void read_file() {
        assert(file_in.good());
        // we will pad some 0 at the tail of huffman code
        if (bit_counter < 32) {
            uint32_t temp_buf = 0;
            uint8_t byte;
            for (int i = 0; i< 4; i++) {
                if (file_in.read(reinterpret_cast<char*>(&byte), sizeof(uint8_t)))
                    temp_buf = (temp_buf << 8) | static_cast<uint32_t>(byte);
                else // dead line.
                    temp_buf = temp_buf << 8;
            }
            read_buf |= static_cast<uint64_t>(temp_buf) << (64 - 32 - bit_counter);
            bit_counter += 32;
        }
    }
};
