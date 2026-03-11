cmake_minimum_required(VERSION 3.25)
project(merge-nikoly_vologdin LANGUAGES C CXX)

add_executable(merge
        heap.cpp
)

target_sources(merge
    PRIVATE
        "main.cpp"
        "dynamic-string.cpp"
    PUBLIC FILE_SET HEADERS FILES
        "dynamic-string.h"
)

ct_set_compiler_warnings(merge)
