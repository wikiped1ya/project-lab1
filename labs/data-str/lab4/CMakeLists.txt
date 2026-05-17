cmake_minimum_required(VERSION 3.10)
project(Lab4 VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(apps)

# Включаем тестирование
enable_testing()
add_subdirectory(tests)

enable_testing()
# add_subdirectory(tests) 
