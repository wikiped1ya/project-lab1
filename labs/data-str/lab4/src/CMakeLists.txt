add_library(list_lib STATIC list.cpp)

target_include_directories(list_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
