cmake_minimum_required(VERSION 3.24)
project(SoundProcessor)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES "source/*.cpp")
add_library(SoundProcessorLib STATIC ${SOURCES})

add_executable(SoundProcessor source/main.cpp)
target_link_libraries(SoundProcessor PRIVATE SoundProcessorLib)


# add_executable(SoundProcessor main.cpp state.h parser.cpp parser.h converter.cpp converter.h editor.cpp editor.h WAV_channel.cpp WAV_channel.h)

