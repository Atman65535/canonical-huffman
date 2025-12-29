//
// Created by atman on 12/26/25.
//
#include <iostream>
#include <filesystem>
#include "canonical_coder.hpp"

using std::cout;
using std::endl;
namespace fs = std::filesystem;

int main(const int argc, const char** argv) {
    if (argc < 3) {
        cout << "Usage : ./roi_huffman <file to extract features.> <label name> \n"
                "example: ./roi_huffman ./img/images.jpeg cat " << endl;
        return 0;
    }
    if (argc == 3) {
        std::string file_name = argv[1];
        std::string label = argv[2];
        const std::string command = "python ./detector/det.py --image_path " + file_name + " --label "+ label;
        system(command.c_str());
        fs::create_directories("./decompressed_crops");
        fs::create_directories("./compressed_crops/");
        for (const auto& entry : fs::directory_iterator("./crops")) {
            if (entry.is_regular_file()) {
                std::cout << "compressing: " << entry.path().string() << endl;
                std::string file_out = "./compressed_crops/" + entry.path().filename().string() + ".tlpress";
                CanonicalEncoderDecoder coder(entry.path(), file_out, true);
                coder.encode();
                std::string file_decompress = "./decompressed_crops/" + entry.path().filename().string();
                CanonicalEncoderDecoder decoder(file_out, file_decompress, false);
                decoder.decode();
            }
        }
    }
    else {
        cout << "Too much arguments." << endl;
        cout << "Usage : ./roi_huffman.cpp <file to extract features.>" << endl;
        return 0;
    }
}