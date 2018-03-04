cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. SRC_LIST)

add_library(midifile ${SRC_LIST})
