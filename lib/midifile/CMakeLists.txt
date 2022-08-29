cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src SRC_LIST)

add_library(midifile ${SRC_LIST})
target_include_directories(midifile INTERFACE src)
