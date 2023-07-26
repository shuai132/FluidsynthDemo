cmake_minimum_required(VERSION 3.1)

project(FluidsynthDemo)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        /usr/local/include
        /opt/homebrew/opt/fluidsynth/include
)
link_directories(
        /usr/local/lib
        /opt/homebrew/opt/fluidsynth/lib
)

add_subdirectory(lib/midifile)

add_executable(midiplayer midiplayer.cpp)
target_link_libraries(midiplayer fluidsynth)

add_executable(mymidiplayer mymidiplayer.cpp)
target_link_libraries(mymidiplayer fluidsynth midifile)

add_executable(midi2h midi2h.cpp)
target_link_libraries(midi2h midifile)

add_executable(midi2h_test midi2h_test.cpp)
target_link_libraries(midi2h_test fluidsynth)
