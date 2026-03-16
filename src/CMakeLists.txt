
project(merge-nikoly_vologdin LANGUAGES C CXX)

add_executable(merge)

target_sources(merge
    PRIVATE
        "main.cpp"
        "dynamic-string.cpp"
        "heap.cpp"
    PUBLIC FILE_SET HEADERS FILES
        "heap.h"
        "dynamic-string.h"
)

ct_set_compiler_warnings(merge)
