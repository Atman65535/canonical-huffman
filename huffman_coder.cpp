//
// Created by atman on 12/24/25.
//
// from canonical_coder import CanonicalCoder
#include "iostream"
#include "canonical_coder.hpp"
#include "canonical_coder.hpp"


int main(int argc, char** argv) {
    // if (argc != 2) {
    //     std::cout << "usage: $TARGET $FILETOCOMPRESS" << std::endl;
    //     return 1;
    // }
    // std::string file_name(argv[1]);
    // std::string file_name = "/home/atman/Pictures/elaina.jpg";
    // CanonicalCoder(file_name, true);

    std::string file_in("/home/atman/Pictures/twilight.jpm");
    std::string file_out("/home/atman/Pictures/twilight1.jpg");
    if (argc == 1) {
        cout << "Helper:\n"
                "./huffcode [Option] <original_file> <save_dir>\n"
                "Options:    \n"
                "       compress: use this file to compress sth\n"
                "       uncompress: literaly.\n"
                "Usage : ./huffcode compress /home/atman/Pictures/twilight.txt /home/atman/Pictures/twilight.wtlcompress\n" << endl;
    }
    else {
        string mode = argv[1];
        file_in = argv[2];
        if (argc == 4)
            file_out = argv[3];
        else file_out = file_in + ".tlpress";
        if (mode == "compress") {

            CanonicalEncoderDecoder encoder_decoder(file_in, file_out, true);
            std::cout << "trying compress..." << std::endl;
            encoder_decoder.encode();
            std::cout << "compress end" << endl;
        }
        else if (mode == "uncompress") {
            CanonicalEncoderDecoder encoder_decoder(file_in, file_out, false);
            std::cout << "trying uncompress..." << std::endl;
            encoder_decoder.decode();
            std::cout << "uncompress end" << endl;
        }
    }
}