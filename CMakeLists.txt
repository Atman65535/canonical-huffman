cmake_minimum_required(VERSION 3.20)

project(huffman
        VERSION 0.1.0
        LANGUAGES CXX
)
set(CMAKE_CXX_COMPILER_VERSION CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nlohmann_json 3.2.0) # optional

add_executable(huffcode huffman_coder.cpp)
target_include_directories(huffcode PRIVATE ./inc)
target_link_libraries(huffcode PRIVATE nlohmann_json::nlohmann_json)

# the roi huffman is just for demonstration. Don't try to change it.
add_executable(roi_huffman roi_huffman.cpp)
target_include_directories(roi_huffman PRIVATE ./inc)
target_link_libraries(roi_huffman PRIVATE nlohmann_json::nlohmann_json)
