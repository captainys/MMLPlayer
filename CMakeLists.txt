cmake_minimum_required(VERSION 3.2)

project(MMLPlayer)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ym2612)
add_subdirectory(mmlplayer)
add_subdirectory(samples)
