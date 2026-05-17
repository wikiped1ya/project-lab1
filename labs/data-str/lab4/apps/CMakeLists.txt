add_executable(lab4 main.cpp)

target_link_libraries(lab4 PRIVATE list_lib)

target_include_directories(lab4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
