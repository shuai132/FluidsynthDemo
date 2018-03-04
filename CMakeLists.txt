cmake_minimum_required(VERSION 2.8)

set(midiplayer "midiplayer")

set(mymidiplayer "mymidiplayer")

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ./lib/fluidsynth
        ./lib/fluidsynth/include

        ./lib/midifile
        )

add_subdirectory(./lib/midifile)

link_directories(./lib/fluidsynth)

add_executable(${midiplayer}
        midiplayer.cpp
        )
target_link_libraries(${midiplayer} fluidsynth)

add_executable(${mymidiplayer}
        mymidiplayer.cpp
        )
target_link_libraries(${mymidiplayer} fluidsynth midifile)
